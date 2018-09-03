#-*- coding: utf-8 -*-

import json

def JSON_to_Dict(jsonData) :
    jsonString = json.dumps(jsonData)
    dict = json.loads(jsonString)
    return dict

def Keys_and_Values_Dict(dictData) :

    for key, value in dictData.items():
        print key, value
