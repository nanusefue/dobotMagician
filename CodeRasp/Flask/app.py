import os
import sqlite3
from flask import Flask, request,json,session,jsonify, g, redirect, url_for, abort, \
     render_template, flash
from werkzeug.utils import secure_filename
DATABASE = 'database/database.db'
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = set(['xml','json','txt'])

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
            insert('json', fields=('name','filename','path','description'), values=(name,filename,os.path.join(app.config['UPLOAD_FOLDER'], filename),description))

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