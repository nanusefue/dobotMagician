import xml.etree.ElementTree as ET
import json
import sys
import argparse
from collections import OrderedDict
from pprint import pprint

class ParserDobotMagicianExport():
	
	def __init__(self, Xml, Json):
		self.Xml = Xml
		self.Json = Json

	def moveType(self,value):
		return {
			'1': "MOVJ",
			'2': "MOVL",
			'3': "UNKOWN",
			'4': "ARC",

		}[value]

	def GenerateJson(self,data):
		with open(self.Json + '.json', 'w') as outfile:
			json.dump(data, outfile)

	def ParserXml(self):
		data = {}
		tree = ET.parse(self.Xml)
		root = tree.getroot()
		i =0
		total=len(root)+1
		rows=OrderedDict()
		for child in root:
			if i<total :
					if child.tag!="row_StudioVersion":
						tmp={}
						tmp['Row']=child.tag
						tmp['PauseTime']=root[i][10].text
						tmp['_R']=root[i][9].text
						tmp['_Z']=root[i][8].text
						tmp['_Y']=root[i][7].text
						tmp['_X']=root[i][6].text
						tmp['R']=root[i][5].text
						tmp['Z']=root[i][4].text
						tmp['Y']=root[i][3].text
						tmp['X']=root[i][2].text
						tmp['MotionStyle']=self.moveType(root[i][0].text)
						tmp['Name']=root[i][1].text
						rows[child.tag]=tmp

			i+=1

		data=rows
		return data

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description='Parser XML Dobot Magician.')
	parser.add_argument('--Xml', required=True, help='Xml generate for DobotMagician Studio')
	parser.add_argument('--Json', required=True, help='File name export json')
	args = parser.parse_args()
	Parser = ParserDobotMagicianExport(args.Xml, args.Json)
	data=Parser.ParserXml()
	Parser.GenerateJson(data)
