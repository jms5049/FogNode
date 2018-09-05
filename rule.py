# -*- coding: utf-8 -*-

class rule:

    temperature = 30.0
    humidity = 100.0
    gas_ppm = 10.0

    def __init__(self,temperature,humidity,gas_ppm):
        self.temperature = temperature
        self.humidity = humidity
        self.gas_ppm = gas_ppm