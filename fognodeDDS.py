# -*- coding: utf-8 -*-

import socket
from rule import *

def set_rule(data):
    temp = data[0]
    humid = data[1]
    gas = data[2]
    rule(temp,humid,gas)

if __name__ == "__main__":

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('#IP ADDRESS', #PORT))
    server_socket.listen(1)
    client_socket, addr = server_socket.accept()

    data = server_socket.recv(1024)
    print(data)



    # set_rule(data)