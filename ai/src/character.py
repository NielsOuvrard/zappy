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
        self.first = True

        # Inventory
        self.inventory = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

        self.lvl = 1

        # create mental map
        self.map = []
        self.pos_x = 0
        self.pos_y = 0

        # Command
        self.buffer = ""
        self.next_command = []

    def parse_response(self, command):
        """
        Remplie self.next_command avec les commandes a faire

        De l'index 0 a len(self.next_command) - 1
        """
        self.buffer += command
        print("PARSED COMMAND = " + command)
        if "\n" in self.buffer:
            while "\n" in self.buffer:
                self.next_command.append(self.buffer.split("\n")[0])
                self.buffer = self.buffer.split("\n", 1)[1]
        else:
            self.parse_response(self.server.recv(1024).decode())

    def look(self):
        self.server.send("Look\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        try:
            response = response[1:-2] #! A FIX AVANT LA FIN DU PROJET
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
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def right(self):
        self.server.send("Right\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def left(self):
        self.server.send("Left\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def getInventory(self):
        self.server.send("Inventory\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        if response == "dead\n":
            return response
        response = response[1:-2] #! A FIX AVANT LA FIN DU PROJET
        response = response.split(",")
        for i in range(len(response)):
            response[i] = response[i].split(" ")
            # remove empty string
            response[i] = list(filter(None, response[i]))
        for i in range(len(response)):
            self.inventory[response[i][0]] = int(response[i][1])
        return self.inventory
        # return response

    def broadcast(self, message):
        self.server.send(("Broadcast " + message + "\n").encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def connect_nbr(self):
        self.server.send("Connect_nbr\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def fork(self):
        self.server.send("Fork\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def eject(self):
        self.server.send("Eject\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def take(self, object):
        self.server.send(("Take " + object + "\n").encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def set(self, object):
        self.server.send(("Set " + object + "\n").encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        return response

    def incantation(self):
        self.server.send("Incantation\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        self.lvl += 1
        return response
