##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## Player
##

import json

class Player:
    def __init__(self, size_x, size_y, id, server):
        self.size_x = size_x
        self.size_y = size_y
        self.id = id
        self.server = server

        # create mental map
        self.map = []
        self.pos_x = 0
        self.pos_y = 0

    def look(self):
        self.server.send("Look\n".encode())
        response = self.server.recv(1024).decode()
        try:
            response = response[1:-2] # bof
        except:
            print("error")
            return []
        response = response.split(",")
        for i in range(len(response)):
            response[i] = response[i].split(" ")
            # remove empty string
            response[i] = list(filter(None, response[i]))
        print(response)
        self.map = []
        for i in range(len(response)):
            case_info: dict = {
                "case_id": i,
                "player": 0,
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            }
            for j in range(len(response[i])):
                case_info[response[i][j]] += 1
            self.map.append(case_info)
        print(json.dumps(self.map, indent=4))
        return response

    def forward(self):
        self.server.send("Forward\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def right(self):
        self.server.send("Right\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def left(self):
        self.server.send("Left\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def inventory(self):
        self.server.send("Inventory\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def broadcast(self, message):
        self.server.send(("Broadcast " + message + "\n").encode())
        response = self.server.recv(1024).decode()
        return response

    def connect_nbr(self):
        self.server.send("Connect_nbr\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def fork(self):
        self.server.send("Fork\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def eject(self):
        self.server.send("Eject\n".encode())
        response = self.server.recv(1024).decode()
        return response

    def take(self, object):
        self.server.send(("Take " + object + "\n").encode())
        response = self.server.recv(1024).decode()
        return response

    def set(self, object):
        self.server.send(("Set " + object + "\n").encode())
        response = self.server.recv(1024).decode()
        return response

    def incantation(self):
        self.server.send("Incantation\n".encode())
        response = self.server.recv(1024).decode()
        return response
