#!/opt/local/bin/python
#-*- coding: utf-8 -*-

import json
import io

f = open("json.txt", "w+")

exampleData = {}
exampleData['a'] = "1"
exampleData['b'] = "2"
num = [1,2,3,4,5,6]
exampleData['num'] = num

f.write(json.dumps(exampleData))
f.close()
