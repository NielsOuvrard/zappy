##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## Player
##

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
            response = response[1:-2]
        except:
            print("error")
            return []
        response = response.replace(",", " ").split()
        print(response)
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
