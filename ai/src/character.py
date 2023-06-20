##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## Player
##

import json
import sys
import subprocess
from enum import Enum

LVL1_2 = {
    "ally": 0,
    "linemate": 1,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
}

LVL2_3 = {
    "ally": 1,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 1,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
}

LVL3_4 = {
    "ally": 1,
    "linemate": 2,
    "deraumere": 0,
    "sibur": 1,
    "mendiane": 0,
    "phiras": 2,
    "thystame": 0
}

LVL4_5 = {
    "ally": 3,
    "linemate": 1,
    "deraumere": 1,
    "sibur": 2,
    "mendiane": 0,
    "phiras": 1,
    "thystame": 0
}

LVL5_6 = {
    "ally": 3,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 1,
    "mendiane": 3,
    "phiras": 0,
    "thystame": 0
}

LVL6_7 = {
    "ally": 5,
    "linemate": 1,
    "deraumere": 2,
    "sibur": 3,
    "mendiane": 0,
    "phiras": 1,
    "thystame": 0
}

LVL7_8 = {
    "ally": 5,
    "linemate": 2,
    "deraumere": 2,
    "sibur": 2,
    "mendiane": 2,
    "phiras": 2,
    "thystame": 1
}

class Priority(Enum):
    Undefined = 0
    Food = 1
    Stones = 2
    Incantation = 3
    Reproduction = 4

class Player:
    def __init__(self, size_x, size_y, id, server):
        self.size_x = size_x
        self.size_y = size_y
        self.id = id
        self.server = server
        self.can_evolve = False
        self.needed_food = 0
        self.leader = False
        self.priority = Priority.Undefined

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
        self.level_cap: list = [LVL1_2, LVL2_3, LVL3_4, LVL4_5, LVL5_6, LVL6_7, LVL7_8]

        # create mental map
        self.map = []
        self.go_case_id = -1
        self.pos_x = 0
        self.pos_y = 0

        # action to do
        self.next_move = []

        # Command
        self.buffer = ""
        self.next_command = []

    def __str__(self):
        return "I'm player " + str(self.id) + " and my inventory is " + str(self.inventory)

    def compute_needed_food(self, case_id):
        """
        Compute the needed food according to the number of foods in the inventory and level
        """
        self.needed_food = (case_id // 2) + 5

    def compute_evolve(self):
        """
        Compute if the player can evolve
        """
        stones: dict = {}
        stones = self.inventory.copy()
        stones.pop("food")
        needed_stones: dict = self.level_cap[self.lvl - 1].copy()
        needed_stones.pop("ally")
        if stones == needed_stones:
            self.can_evolve = True
        else:
            self.can_evolve = False


    def compute_priority(self):
        """
        This function compute the priority of the player
        """
        self.compute_needed_food(self.map[-1].get("case_id"))
        self.compute_evolve()
        if self.inventory["food"] < self.needed_food:
            self.priority = Priority.Food
        elif self.lvl > 1 and self.can_evolve:
            self.priority = Priority.Reproduction
        elif self.can_evolve and self.inventory["food"] >= 6:
            self.priority = Priority.Incantation
        else:
            self.priority = Priority.Stones

    def compute_good_case(self):
        """
        According to the map, this function compute the best case to go
        """
        self.compute_priority()
        self.go_case_id = -1
        for i in range(len(self.map)):
            if self.map[i]["player"] == 0:
                if self.priority == Priority.Food and self.map[i]["food"] > 0:
                    self.go_case_id = self.map[i]["case_id"]
                    break
                elif self.priority == Priority.Stones:
                    print("LEVEL CAP ", self.level_cap[self.lvl - 1])
                    needed_stones: dict = self.level_cap[self.lvl - 1].copy()
                    needed_stones.pop("ally")
                    for stone in needed_stones:
                        if self.map[i][stone] > 0 and self.inventory[stone] < needed_stones[stone]:
                            self.go_case_id = self.map[i]["case_id"]
                            break
                # elif self.priority == Priority.Incantation:
                #     if self.map[i]["player"] > 0 and i != 0:
                #         self.go_case_id = self.map[i]["case_id"]
                #         break
                # elif self.priority == Priority.Reproduction:
                #     if self.map[i]["ally"] > 0:
                #         self.go_case_id = self.map[i]["case_id"]
                #         break

    def go_to_case(self):
        """
        This function compute the next action to do to go to the case
        """
        if self.go_case_id == -1:
            self.compute_good_case()
        if self.go_case_id == 0:
            self.next_move.append("Take")
        self.next_move = []

        # forward
        total = 0
        line = 1
        while total < self.go_case_id:
            total += line * 2 + 1
            line += 1
        mov = 1
        while mov < line:
            self.next_move.append("Forward")
            mov += 1

        # turn
        line -= 1
        actual_line_size = line * 2 + 1
        self.go_case_id = self.go_case_id - (total - actual_line_size)
        x = -(actual_line_size) + self.go_case_id + (actual_line_size // 2)
        if x < 0:
            self.next_move.append("Left")
        elif x > 0:
            self.next_move.append("Right")
        else:
            return
        # forward after turn
        mov = 0
        while mov < abs(x):
            self.next_move.append("Forward")
            mov += 1
        return

    def get_stone(self):
        """
        This function compute the next action to do to get the stone
        """
        needed_stones: dict = self.level_cap[self.lvl - 1].copy()
        needed_stones.pop("ally")
        for stone in needed_stones:
            if self.inventory[stone] < needed_stones[stone]:
                return stone

    def compute_action(self):
        """
        This function compute the next action to do according to the priority enum
        """
        self.go_case_id = -1
        self.go_to_case()
        if self.priority == Priority.Food:
            self.next_move.append("food")
        elif self.priority == Priority.Stones:
            self.next_move.append(self.get_stone())
            print("SEARCHING FOR STONE", self.get_stone())
        elif self.priority == Priority.Reproduction:
            self.next_move.append("Fork")
        elif self.priority == Priority.Incantation:
            if self.level_cap[self.lvl - 1]["ally"] != 0:
                d = 0 #TODO A faire pour le Broadcast
            else:
                self.next_move.append("Incantation")
        else:
            self.next_move.append("food")
        print("NEXT COMMAND", self.next_move)

    def parse_response(self, command):
        """
        Remplie self.next_command avec les commandes a faire

        De l'index 0 a len(self.next_command) - 1
        """
        self.buffer += command
        print("PARSED COMMAND = " + command)
        print(f"NEXT COMMAND {self.next_command}")
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
            response = response[1:-1]
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
            sys.exit(84)
            return response
        response = response[1:-1]
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

    def fork(self, data: dict):
        self.server.send("Fork\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        subprocess.Popen(["./zappy_ai", "-p", str(data["port"]), "-n", str(data["team_name"]), "-h", str(data["host"])])
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

    def drop_stone(self):
        # according to current level cap and inventory drop all needed stones to pass to the next level
        needed_stones: dict = self.level_cap[self.lvl - 1].copy()
        needed_stones.pop("ally")
        for stone in needed_stones:
            if self.inventory[stone] >= needed_stones[stone]:
                for i in range(needed_stones[stone]):
                    self.set(stone)

    def incantation(self):
        self.drop_stone()
        self.server.send("Incantation\n".encode())
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        if response != "ko\n":
            self.lvl += 1
        self.parse_response(self.server.recv(1024).decode())
        response = self.next_command.pop(0)
        print("LEVEL = ", self.lvl)
        return response
