# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
from influxDB import database
from rule import rule
import ast

def on_connect(client, userdata, flags, rc):
    print ("Connected with result code " + str(rc))
    client.subscribe("test_fognode")

def on_message(client, userdata, msg):
    print "Topic: ", msg.topic + '\nMessage: ' + str(msg.payload)

    try:
        temp = msg.payload
        temp = temp.split(':')
        data = {temp[0] : strTofloat(temp[1])}
        db.insert(data)
        remote_control(temp[0],strTofloat(temp[1]))
    except:
        print('error')


def strTofloat(msg):
    return float(msg)


def remote_control(key, value):

    dict_rule = rule.__dict__

    if key in dict_rule:
        retention = dict_rule[key]

        if value > retention:
            client.publish("f2a",key)


if __name__ == "__main__":

    #mqtt
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("iot.eclipse.org", 1883, 60)
    #db setup
    db = database("localhost",8086)

    #mqtt    
    client.loop_forever()

    #dds