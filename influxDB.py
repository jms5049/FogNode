# -*- coding: utf-8 -*-

import time
from influxdb import InfluxDBClient


class database():
    """database"""

    is_exist = False

    def __init__(self, host, port):
        self.host = host
        self.port = port

    def insert(self, jsons):
        """Instantiate a connection to the InfluxDB.
        """
        user = "user"
        # config.CONFIG['id']
        password = "password"
        # config.CONFIG['password']
        dbname = "smartfarm"
        # config.CONFIG['dbname']
        timestamp = time.strftime('%Y-%m-%dT%H:%M:%SZ', time.localtime())
        print(timestamp)