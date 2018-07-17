import xml.etree.ElementTree as ET
import json
import sys
import argparse

class ParserDobotMagicianExport():
	
	def __init__(self, Xml, Json):
		self.Xml = Xml
		self.Json = Json
"""Falta por implementar movimientos del robot"""

	def moveType(self,value):
		return {
			'0': "JUMPXYZ",
			'1': "MOVJ",
			'2': "MOVL",
			'3': "JUMPANGLE",
			'4': "MOVJANGLE",
			'5': "MOVLANGLE",
			'6': "MOVJANGLEINC",
			'7': "MOVLXYZIN",
			'8': "MOVJXYZIN",
			'9': "JUMPMOVL"
		}[value]

	def GenerateJson(self,data):
		json_data = json.dumps(data)
		with open(self.Json + '.json', 'w') as outfile:
			json.dump(data, outfile)

	def ParserXml(self):
		data = {}
		json_data = json.dumps(data)
		tree = ET.parse(self.Xml)
		root = tree.getroot()
		i =0
		total=len(root)+1
		rows={}
		rows['rows']={}
		array={}
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
						tmp['MotionStyle']=moveType(root[i][0].text)
						tmp['Name']=root[i][1].text
						array[i]=tmp

			i+=1

		rows['rows']=array	
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
