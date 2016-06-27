#!/opt/local/bin/python
#-*- coding: utf-8 -*-

import json
import io

data = []
# Json file name here
json_file = "File name here"
input_file  = file(json_file, "r")
for line in input_file:
	data.append(json.loads(line))

for obj in data:
	key = "Json key"
	print "Json data: %s %s" % (key, obj[key])