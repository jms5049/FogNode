# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
from influxDB import database
from rule import rule
import ast

def on_connect(client, userdata, flags, rc):
    print ("Connected with result code " + str(rc))
    client.subscribe("test_fognode")

