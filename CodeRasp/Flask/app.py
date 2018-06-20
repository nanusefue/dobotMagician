import os
import sqlite3
from flask import Flask, request,json,session,jsonify, g, redirect, url_for, abort, \
     render_template, flash
from werkzeug.utils import secure_filename
DATABASE = 'database/database.db'
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = set(['xml'])
import time
import datetime

import sys
sys.path.insert(0, 'script')

from dobot_parser import ParserDobotMagicianExport
from dobot_run import RunDobot

#context = ssl.SSLContext(ssl.PROTOCOL_SSLv23)
#context.load_cert_chain('server.crt', 'server.key')
import pprint
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

@app.route("/")
def hello():
    return redirect('/json/list')


@app.route('/json/create',methods=['GET', 'POST'])
def uploadXml():
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        # if user does not select file, browser also
        # submit a empty part without filename
        if file.filename == '':
            file = request.files['file']
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            name=request.form['name']
            description=request.form['description']
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            insert('json', fields=('name','filename','path','description','date'), values=(name,filename,os.path.join(app.config['UPLOAD_FOLDER'], filename),description,datetime.datetime.now().strftime("%m-%d-%Y %H:%M")))

            return redirect(url_for('uploadXmlList',
                                    filename=filename))

    return render_template('uploadxml.html')



@app.route('/json/list')
def uploadXmlList():
    if request.method == 'GET' :
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from json')
        result=rv.fetchall()
        cur.close()

    return render_template('uploadxmlist.html',lista=result)


@app.route('/json/delete',methods=['GET'])
def uploadXmlDelete():
    if request.method == 'GET' :
        _id=request.args.get('id')
        path=request.args.get('path')
        os.remove(os.path.join(path))
        db =  get_db()
        cur=db.cursor()
        rv= db.execute('delete from json WHERE id = ?', [_id])
        db.commit()
        cur.close()

    return redirect('/json/list')



@app.route('/json/view',methods=['GET'])
def uploadXmlView():
    if request.method == 'GET' :
        _id=request.args.get('id')
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from json WHERE id = ?', [_id])
        result=rv.fetchone()
        cur.close()
        text = open(result['path'], 'r+')
        content = text.read()
        text.close()


    return render_template('uploadxmview.html',lista=result,file=content)


@app.route('/dobot/create',methods=['GET'])
def dobotCreate():
    if request.method == 'GET' :
        _id=request.args.get('id')
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from json WHERE id = ?', [_id])
        result=rv.fetchone()
        cur.close()
        Parser = ParserDobotMagicianExport(result['path'],result['name'])
        data=Parser.ParserXml()
        with open(os.path.join(app.config['UPLOAD_FOLDER'], result['name']+'.json'), 'w') as outfile:
            json.dump(data, outfile)

        filename=result['name']+".json"
        insert('dobot', fields=('name','filename','path','description','date'), values=(result['name'],filename,os.path.join(app.config['UPLOAD_FOLDER'], filename),result['description'],datetime.datetime.now().strftime("%m-%d-%Y %H:%M")))




    return render_template('dobotcreate.html',lista=result)


@app.route('/dobot/list')
def dobotList():
    if request.method == 'GET' :
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from dobot')
        result=rv.fetchall()
        cur.close()

    return render_template('dobotlist.html',lista=result)

@app.route('/dobot/view')
def dobotView():
    if request.method == 'GET' :
        _id=request.args.get('id')
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from dobot WHERE id = ?', [_id])
        result=rv.fetchone()
        cur.close()
        text = open(result['path'], 'r+')
        content = text.read()
        text.close()

    return render_template('dobotview.html',lista=result,file=content)

@app.route('/dobot/run')
def dobotRun():
    if request.method == 'GET' :
        _id=request.args.get('id')
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('select * from dobot WHERE id = ?', [_id])
        result=rv.fetchone()
        cur.close()
        filename=os.path.join(app.config['UPLOAD_FOLDER'], result['name']+'.json')
        R = RunDobot(filename)
        R.Connect()
        R.ParserMove()
  
    return render_template('dobotview.html',lista=result)



@app.route('/dobot/main')
def dobotMain():
    if request.method == 'GET' :
        _id=request.args.get('id')
        db =  get_db()
        db.row_factory = sqlite3.Row
        cur=db.cursor()
        rv= db.execute('update dobot set main=1 WHERE id = ?', [_id])
        db.commit()
        cur.close()
    return dobotList()


@app.route('/dobot/delete',methods=['GET'])
def dobotDelete():
    if request.method == 'GET' :
        _id=request.args.get('id')
        path=request.args.get('path')
        os.remove(os.path.join(path))
        db =  get_db()
        cur=db.cursor()
        rv= db.execute('delete from dobot WHERE id = ?', [_id])
        db.commit()
        cur.close()

    return redirect('/dobot/list')


def get_db():
    db = sqlite3.connect(DATABASE)
    return db

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


def insert(table, fields=(), values=()):
    db =  get_db()
    cur=db.cursor()
    query = 'INSERT INTO %s (%s) VALUES (%s)' % (
    table,
        ', '.join(fields),
        ', '.join(['?'] * len(values))
    )
    cur.execute(query, values)
    db.commit()
    id = cur.lastrowid
    cur.close()

if __name__ == '__main__':
    app.run(debug=True,host='0.0.0.0')