##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## network
##

import socket
import sys
import select

class Network:
    def __init__(self, data):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.server.connect((data["host"], data["port"]))
        except ConnectionRefusedError:
            print("Error: Connection refused to: " + data["host"] + ":" + str(data["port"]))
            sys.exit(84)

        self.buffer = ""

    def send(self, message):
        self.server.send((message + "\n").encode())

    def recv(self):
        while "\n" not in self.buffer:
            select.select([self.server], [], [])
            self.buffer += self.server.recv(1024).decode()
        message = self.buffer.split("\n")[0]
        self.buffer = self.buffer[len(message) + 1:]
        return message

    def close(self):
        self.server.close()
