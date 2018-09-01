# -*- coding: utf-8 -*-

import time
from influxdb import InfluxDBClient


class database():
    """database"""

    is_exist = False

    def __init__(self, host, port):
        self.host = host
        self.port = port

    