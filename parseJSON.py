#-*- coding: utf-8 -*-

import json

def JSON_to_Dict(jsonData) :
    jsonString = json.dumps(jsonData)
    dict = json.loads(jsonString)
    return dict

def Keys_and_Values_Dict(dictData) :

    for key, value in dictData.items():
        print key, value

def data_to_json(data) :
    if type(data) is str : 
        return '"' + data + '"' 
    elif type(data) is list : 
	return list_to_json(data, data_to_json)
    elif type(data) is int or type(data) is float : 
        return data.__str__() 
    elif type(data) is dict : 
        return dict_to_json(data, data_to_json) 
    else :
        print("type?� {}".format(type(data)))
        return '""'
