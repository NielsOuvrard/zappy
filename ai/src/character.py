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
from time import sleep

from network import Network
from logger import Logger

# look for food
# enought food -> look for stone
# enought stone -> broadcast "Playler my level ?"
# if find my level -> gather players -> drop stone -> incantation
# if not -> fork & move

# shared inventory ?

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
    Gather = 5

class TypeResponse(Enum):
    BOOL = 0
    INVENTORY = 1
    LOOK = 2
    BROADCAST = 3

class Player:
    def __init__(self, size_x, size_y, id, server: Network):
        self.size_x = size_x
        self.size_y = size_y
        self.id = id
        self.boolean_received = 0
        self.boolean_awaited = 0
        self.data_received = 0
        self.data_awaited = 0
        self.broadcast_specific = False
        self.server = server
        self.can_evolve = False
        self.needed_food = 0
        self.leader = False
        self.priority = Priority.Undefined
        self.forked_nbr = 0
        self.message_received: list = []
        self.message_type_received: list = []
        self.current_action = "NONE"
        self.nmb_player = 1
        self.players: dict = []
        self.shared_inventory = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

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
        evolvable: bool = True
        for key in stones:
            if stones[key] < needed_stones[key]:
                evolvable = False
                break
        self.can_evolve = evolvable
        # if stones == needed_stones:
        #     self.can_evolve = True
        # else:
        #     self.can_evolve = False

    def compute_priority(self):
        """
        This function compute the priority of the player
        """
        if (len(self.map) == 0):
            sleep(0.1)
            Logger.log_err("Player map is empty", self.id)
            return
        self.compute_needed_food(self.map[-1].get("case_id"))
        self.compute_evolve()
        if self.inventory["food"] < self.needed_food:
            Logger.log_warn("food : " + str(self.inventory["food"]) + " needed : " + str(self.needed_food), self.id)
            self.priority = Priority.Food
        elif self.nmb_player < self.level_cap[self.lvl - 1]["ally"] + 1 and self.forked_nbr < 1:
            self.priority = Priority.Reproduction
        elif self.can_evolve and self.inventory["food"] >= 6:
            if self.lvl > 1:
                self.priority = Priority.Gather
            else:
                self.priority = Priority.Incantation
        else:
            self.priority = Priority.Stones

    def compute_good_case(self):
        """
        According to the map, this function compute the best case to go
        """
        self.compute_priority()
        Logger.log_prio("Priority " + str(self.priority), self.id)
        self.go_case_id = -1
        for i in range(len(self.map)):
            if self.map[i]["player"] == 0:
                if self.priority == Priority.Food and self.map[i]["food"] > 0:
                    self.go_case_id = self.map[i]["case_id"]
                    break
                elif self.priority == Priority.Stones:
                    needed_stones: dict = self.level_cap[self.lvl - 1].copy()
                    needed_stones.pop("ally")
                    for stone in needed_stones:
                        if self.map[i][stone] > 0 and self.inventory[stone] < needed_stones[stone]:
                            Logger.log_prio("I need " + stone)
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
        elif self.priority == Priority.Reproduction:
            self.next_move.append("Fork")
        elif self.priority == Priority.Incantation:
            if self.level_cap[self.lvl - 1]["ally"] > (self.map[0]["player"] - 1):
                self.next_move.append("Broadcast Searching_incant_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.id))
                d = 0 #TODO A faire pour le Broadcast
            else:
                self.next_move.append("Incantation")
        else:
            self.next_move.append("food")

    def manage_receive_message(self, response):
        tmp = response.split(" ")
        orientation = int(tmp[1][:-1])
        message = tmp[2]
        # uncrypt message
        message = ''.join(chr(ord(a) ^ 1) for a in message)

        Logger.log_recve("MESSAGE recieve [" + message + "]", self.id)

        if message.startswith("Hello"):
            self.id += 1
            if self.id == 1:
                Logger.log_info("New player spawn, all id + 1")
                self.broadcast_specific = True
            return

        if message.startswith("SharedInventory"):
            message = message.split("_")
            if len(message) != 3:
                Logger.log_err("SharedInventory message too short ->" + str(message) , self.id)
                return
            self.shared_inventory[message[1]] = int(message[2])
            Logger.log_err("SharedInventory [" + message[1] + "] [" + message[2] + "]", self.id)
            Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            return

        if message.startswith("SharedAddInventory"):
            message = message.split("_")
            if len(message) != 3:
                Logger.log_err("SharedAddInventory bad args short ->" + str(message) , self.id)
                return
            self.shared_inventory[message[1]] += int(message[2])
            Logger.log_err("SharedAddInventory [" + message[1] + "] add [" + message[2] + "]", self.id)
            Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            return

        if message.startswith("SharedAllInventory"):
            # TODO int nmbr of player
            message = message.split("_")
            if len(message) != 1 + 2 * len(self.shared_inventory):
                Logger.log_err("SharedAllInventory message too short ->" + str(message) , self.id)
                return
            for i in range(1, len(message), 2):
                self.shared_inventory[message[i]] = int(message[i + 1])
            Logger.log_err("SharedAllInventory " + str(self.shared_inventory) , self.id)
            Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            return

        if message.startswith("myidis"):
            # TODO decrem if player die
            message = message.split("_")
            if len(message) > 1 and int(message[1]) + 1 > self.nmb_player:
                self.nmb_player = int(message[1]) + 1
            for i in self.players:
                if i["id"] == int(message[1]):
                    i["lvl"] = int(message[2])
                    return
            self.players.append({"id": int(message[1]), "lvl": int(message[2])})
            Logger.log_warn("players -> " + str(self.players), self.id)
            if self.id == 0:
                self.broadcast_specific = True
                self.next_move.append("Broadcast myidis_" + str(self.id) + "_" + str(self.lvl))
            return

        return
        # if tmp[2].startswith("Searching_incant_"):
        #     message = tmp[2].split("_")
        #     if int(message[2]) != self.lvl:
        #         return
        #     if int(message[3]) < self.inventory["food"]:
        #         self.next_move.append("Broadcast COME_" + message[4] + "_" + str(self.inventory["food"]) + "_" + str(self.id))
        #         return
        #     if int(message[3]) > self.inventory["food"]:
        #         self.next_move.append("Broadcast WAIT_" + message[4] + "_" + str(self.id))
        #         return

        # if tmp[2].startswith("COME_"):
        #     message = tmp[2].split("_")
        #     if int(message[2]) != self.id:
        #         return
        #     self.next_move.append("Forward")
        #     return

        # if tmp[2].startswith("WAIT_"):
        #     message = tmp[2].split("_")
        #     if int(message[2]) != self.id:
        #         return
        #     self.next_move.append("Forward")

    def manage_response(self) -> None:
        response = self.server.recv()

        if response == "dead":
            sys.exit(0)

        self.message_received.append(response)
        Logger.log_recve(response, self.id)
        # Logger.log_info("last 3 message received -> " + str(self.message_received[-3:]), self.id)

        if response == "Elevation underway" and self.current_action != "INCANTATION":
            Logger.log_err("Elevation underway but not incantation", self.id)
            return

        elif response.startswith("Current level: "):
            if self.lvl != int(response.split(" ")[2]):
                self.broadcast_specific = True
                self.next_move.append("Broadcast myidis_" + str(self.id) + "_" + str(self.lvl))
                self.lvl = int(response.split(" ")[2])
                Logger.log_err("lvl up to " + str(self.lvl), self.id)
            else:
                Logger.log_err("lvl up but same lvl", self.id)
            self.boolean_received += 1
            self.message_type_received.append(TypeResponse.BOOL)
            return

        elif response.startswith("message "):
            self.manage_receive_message(response)
            self.message_type_received.append(TypeResponse.BROADCAST)
            return

        elif response.startswith("Eject: "):
            Logger.log_err("I'VE BEEN EJECTED")
            return

        if response.startswith("[") and response.endswith("]"):
            # * check if inventory or look
            try:
                response = response[1:-1]
            except:
                Logger.log_err("look or inv", self.id)
                return []
            response = response.split(",")
            for i in range(len(response)):
                response[i] = response[i].split(" ")
                # remove empty string
                response[i] = list(filter(None, response[i]))

            self.data_received += 1
            # if inventory
            if len(response) == 7:
                self.message_type_received.append(TypeResponse.INVENTORY)
                new_inventory = {}
                for i in range(len(response)):
                    if len(response[i]) == 2:
                        new_inventory[response[i][0]] = int(response[i][1])
                    else:
                        Logger.log_err("inventory error |" + str(response[i]) + "|", self.id)
                Logger.log_info("inventory = " + str(response), self.id)
                inventory_change: bool = False
                update_inventory = "SharedAddInventory"
                for i in self.inventory:
                    if self.inventory[i] != new_inventory[i]:
                        if i != "food":
                            update_inventory += "_" + i + "_" + str(new_inventory[i] - self.inventory[i])
                            inventory_change = True
                        self.inventory[i] = new_inventory[i]
                if inventory_change:
                    Logger.log_err("update_inventory " + update_inventory, self.id)
                    self.broadcast(update_inventory)
                return
            self.message_type_received.append(TypeResponse.LOOK)
            Logger.log_info("look", self.id)
            # if look
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
                    if len(response[i]) >= j and response[i][j] in case_info:
                        case_info[response[i][j]] += 1
                    else:
                        Logger.log_err("look error |" + str(response[i]) + "|", self.id)
                self.map.append(case_info)
            return
        if response == "ok" or response == "ko":
            self.message_type_received.append(TypeResponse.BOOL)
            self.boolean_received += 1
        return


    def look(self) -> list:
        self.server.send("Look\n")
        self.current_action = "LOOK"
        Logger.log_info("await look", self.id)
        self.data_awaited += 1
        last_nmbr = self.data_received
        while self.data_received < self.data_awaited:
            if last_nmbr != self.data_received:
                last_nmbr = self.data_received
                Logger.log_debug("look " + str(self.data_received) + "/" + str(self.data_awaited), self.id)
            pass
        Logger.log_debug("data_awaited (look) = " + str(self.data_awaited) + " recv = " + str(self.data_received), self.id)

    def forward(self) -> str:
        self.server.send("Forward\n")
        self.current_action = "FORWARD"
        self.boolean_awaited += 1
        # last_nmbr = self.boolean_received
        # Logger.log_info("awaiting forward", self.id)
        # while self.boolean_received < self.boolean_awaited:
        #     if last_nmbr != self.boolean_received:
        #         last_nmbr = self.boolean_received
        #         Logger.log_debug("forward " + str(self.boolean_received) + "/" + str(self.boolean_awaited), self.id)
        #     pass
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! forward error, recve " + str(self.message_received[-1]) , self.id)
        # Logger.log_debug("boolean_awaited (forward) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)

    def right(self) -> str:
        self.server.send("Right\n")
        self.current_action = "RIGHT"
        self.boolean_awaited += 1
        # last_nmbr = self.boolean_received
        # Logger.log_info("awaiting right", self.id)
        # while self.boolean_received < self.boolean_awaited:
        #     if last_nmbr != self.boolean_received:
        #         last_nmbr = self.boolean_received
        #         Logger.log_debug("right " + str(self.boolean_received) + "/" + str(self.boolean_awaited), self.id)
        #     pass
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! right error, recve " + str(self.message_received[-1]) , self.id)
        # Logger.log_debug("boolean_awaited (right) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)

    def left(self) -> str:
        self.server.send("Left\n")
        self.current_action = "LEFT"
        self.boolean_awaited += 1
        # last_nmbr = self.boolean_received
        # Logger.log_info("awaiting left", self.id)
        # while self.boolean_received < self.boolean_awaited:
        #     if last_nmbr != self.boolean_received:
        #         last_nmbr = self.boolean_received
        #         Logger.log_debug("left " + str(self.boolean_received) + "/" + str(self.boolean_awaited), self.id)
        #     pass
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! left error, recve " + str(self.message_received[-1]) , self.id)
        # Logger.log_debug("boolean_awaited (left) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)

    def getInventory(self):
        self.server.send("Inventory\n")
        self.current_action = "INVENTORY"
        Logger.log_debug("await inventory", self.id)
        self.data_awaited += 1
        while self.data_received < self.data_awaited:
            pass
        Logger.log_debug("inventory receve", self.id)

    def broadcast(self, message):
        Logger.log_info("broadcasting " + message, self.id)
        if self.broadcast_specific:
            self.broadcast_specific = False
            self.broadcast("myidis_" + str(self.id) + "_" + str(self.lvl))
            Logger.log_info("myidis", self.id)
            if self.id == 1:
                inventory_empty = True
                for i in self.shared_inventory:
                    if self.shared_inventory[i] != 0:
                        inventory_empty = False
                if inventory_empty:
                    return
                str_to_send = "SharedAllInventory"
                for i in self.shared_inventory:
                    str_to_send += "_" + i + "_" + str(self.shared_inventory[i])
                self.broadcast(str_to_send)
                Logger.log_err("SharedAllInventory " + str_to_send, self.id)
                Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            return
        # uncrypt message
        message = ''.join(chr(ord(a) ^ 1) for a in message)
        self.server.send(("Broadcast " + message + "\n"))
        self.current_action = "BROADCAST"
        self.boolean_awaited += 1
        # last_nmbr = self.boolean_received
        # # can only send ok
        # Logger.log_info("awaiting broadcast", self.id)
        while self.boolean_received < self.boolean_awaited:
            # sleep(0.1)
            # Logger.log_debug("broadcast " + str(self.boolean_received) + "/" + str(self.boolean_awaited), self.id)
            pass
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! broadcast error, recve " + str(self.message_received[-1]) , self.id)
        Logger.log_debug("boolean_awaited (broadcast) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)

    def connect_nbr(self):
        self.server.send("Connect_nbr\n")
        self.current_action = "CONNECT_NBR"

    def fork(self, data: dict):
        self.server.send("Fork\n")
        self.current_action = "FORK"
        subprocess.Popen(["./zappy_ai", "-p", str(data["port"]), "-n", str(data["team_name"]), "-h", str(data["host"])])
        self.forked_nbr += 1
        self.boolean_awaited += 1
        # can only send ok
        Logger.log_info("awaiting fork", self.id)
        while self.boolean_received < self.boolean_awaited:
            pass
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! fork error, recve " + str(self.message_received[-1]) , self.id)
        Logger.log_debug("boolean_awaited (fork) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)

    def eject(self):
        self.server.send("Eject\n")
        self.current_action = "EJECT"
        self.boolean_awaited += 1
        Logger.log_debug("boolean_awaited (eject) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)
        # return self.response

    def take(self, object):
        self.server.send(("Take " + object + "\n"))
        self.current_action = "TAKE"
        self.boolean_awaited += 1
        last_nmbr = self.boolean_received
        Logger.log_info("awaiting take", self.id)
        while self.boolean_received < self.boolean_awaited:
            pass
        if self.message_received[-1] == "ok":
            self.inventory[object] += 1
            if object != "food":
                self.shared_inventory[object] += 1
                self.broadcast("SharedAddInventory_" + object + "_1")
                Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            # Logger.log_debug("take " + object + " success = " + str(self.inventory[object]), self.id)
        else:
            Logger.log_err("take error, no " + object + " on the ground", self.id)

    def set(self, object):
        self.server.send(("Set " + object + "\n"))
        self.current_action = "SET"
        self.boolean_awaited += 1
        Logger.log_info("awaiting set " + object, self.id)
        while self.boolean_received < self.boolean_awaited:
            pass
        if self.message_received[-1] == "ok":
            self.inventory[object] -= 1
            if object != "food":
                self.shared_inventory[object] -= 1
                self.broadcast("SharedAddInventory_" + object + "_-1")
                Logger.log_err("self.shared_inventory ->" + str(self.shared_inventory), self.id)
            # Logger.log_debug("set " + object + " success", self.id)
        else:
            Logger.log_err("set error, no " + object + " in inventory", self.id)
        # return self.response

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
        self.server.send("Incantation\n")
        self.current_action = "INCANTATION"
        # check with last response if incantation is ok
        self.boolean_awaited += 1
        Logger.log_info("awaiting incantation answer", self.id)
        while self.boolean_received < self.boolean_awaited:
            pass
        if self.message_received[-1] == "ko":
            Logger.log_err("incantation ko", self.id)
        else:
            Logger.log_success("player " + str(self.id) + " level up to " + str(self.lvl), self.id)
