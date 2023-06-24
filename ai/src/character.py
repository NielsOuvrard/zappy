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
        self.server = server
        self.can_evolve = False
        self.needed_food = 0
        self.leader = False
        self.action_done = True
        self.priority = Priority.Undefined
        self.forked_nbr = 0
        self.message_received: list = []
        self.message_type_received: list = []
        self.current_action = "NONE"
        self.nmb_player = 1
        self.players: dict = []
        self.shared_inventory_my_level: list = []

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
        Logger.log_info("Compute evolve : " + str(self.lvl) + " " + str(self.inventory["food"]) + " " + str(self.needed_food) + " " + str(self.map[0]["linemate"]))
        if self.lvl == 1 and self.inventory["food"] >= self.needed_food and self.map[0]["linemate"] >= 1:
            Logger.log_info("I can evolve", self.id)
            self.can_evolve = True
            self.go_case_id = 0
            return
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

    def compute_priority(self) -> bool:
        """
        This function compute the priority of the player
        """
        if (len(self.map) == 0):
            self.priority = Priority.Food
            Logger.log_err("Player map is empty", self.id)
            return False
        self.compute_needed_food(self.map[-1].get("case_id"))
        self.compute_evolve()
        if self.inventory["food"] < self.needed_food:
            Logger.log_warn("food : " + str(self.inventory["food"]) + " needed : " + str(self.needed_food), self.id)
            self.priority = Priority.Food
            return False
        elif self.nmb_player < self.level_cap[self.lvl - 1]["ally"] + 1 and self.forked_nbr < 1:
            self.priority = Priority.Reproduction
            return True
        elif self.can_evolve and self.inventory["food"] >= 6:
            if self.lvl > 1:
                self.priority = Priority.Gather
                return False
            else:
                self.priority = Priority.Incantation
                return True
        else:
            self.priority = Priority.Stones
            return False

    def compute_good_case(self):
        """
        According to the map, this function compute the best case to go
        """
        # self.compute_priority()
        # Logger.log_prio("Priority " + str(self.priority), self.id)

        # ? is this check necessary ?
        if self.priority == Priority.Reproduction or self.priority == Priority.Incantation:
            Logger.log_err("Priority is reproduction or incantation in (compute_good_case)", self.id)
            self.go_case_id = 0
            return
        self.go_case_id = -1
        for i in range(len(self.map)):
            # if self.map[i]["player"] == 0:
            if self.priority == Priority.Food and self.map[i]["food"] > 0:
                self.go_case_id = i
                # self.go_case_id = self.map[i]["case_id"]
                return
            elif self.priority == Priority.Stones:
                needed_stones: dict = self.level_cap[self.lvl - 1].copy()
                needed_stones.pop("ally")
                for stone in needed_stones:
                    if self.map[i][stone] > 0 and self.inventory[stone] < needed_stones[stone]:
                        Logger.log_prio("I need " + stone)
                        self.go_case_id = self.map[i]["case_id"]
                        return
            elif self.priority == Priority.Gather:
                Logger.log_prio("Need to Gather", self.id)
            # elif self.priority == Priority.Incantation:
            #     if self.map[i]["player"] > 0 and i != 0:
            #         self.go_case_id = self.map[i]["case_id"]
            #         break
            # elif self.priority == Priority.Reproduction:
            #     if self.map[i]["ally"] > 0:
            #         self.go_case_id = self.map[i]["case_id"]
            #         break

    def go_to_case(self) -> bool:
        """
        This function compute the next action to do to go to the case
        """
        # todo: put it somewhere else
        Logger.log_warn("go to case " + str(self.go_case_id), self.id)
        if self.go_case_id == -1:
            Logger.log_prio("No case to go -1", self.id)
            for i in range(self.lvl):
                self.forward()
            return False

        # self.go_case_id = -1
        if self.go_case_id == 0:
            Logger.log_prio("No case to go 0", self.id)
            return True
        #     self.next_move.append("Take")
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
            Logger.log_warn("so we do " + str(self.next_move) + "\n", self.id)
            return True
        # forward after turn
        mov = 0
        while mov < abs(x):
            self.next_move.append("Forward")
            mov += 1
        Logger.log_warn("so we do " + str(self.next_move) + "\n", self.id)
        return True

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
        if self.priority == Priority.Food:
            self.next_move.append("food")
        elif self.priority == Priority.Stones:
            self.next_move.append(self.get_stone())
        elif self.priority == Priority.Reproduction:
            self.next_move.append("Fork")
        elif self.priority == Priority.Gather:
            Logger.log_prio("Need to Gather (compute_action)", self.id)
            # if self.level_cap[self.lvl - 1]["ally"] > (self.map[0]["player"] - 1):
            #     self.next_move.append("Broadcast Searching_incant_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.id))
            #     d = 0 #TODO A faire pour le Broadcast
            # else:
        elif self.priority == Priority.Incantation:
            self.next_move.append("Incantation")
        else:
            self.next_move.append("food")

    def find_next_move_with_priority(self):
        # fill self.go_case_id
        self.compute_good_case()
        # fill self.next_move
        find_good_tile = self.go_to_case()
        if find_good_tile:
            self.compute_action()

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
            for player in self.players:
                player["id"] += 1
            for player in self.shared_inventory_my_level:
                player["id"] += 1
            new_player = {
                "id": 0,
                "orientation": 0, # default value
                "lvl": 1,
                "food": 10, # default value
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            }
            self.players.append(new_player)
            allMyInfo = "AllMyInfo_" + str(self.id) + "_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.inventory["linemate"]) + "_" + str(self.inventory["deraumere"]) + "_" + str(self.inventory["sibur"]) + "_" + str(self.inventory["mendiane"]) + "_" + str(self.inventory["phiras"]) + "_" + str(self.inventory["thystame"])
            self.next_move.append("Broadcast " + allMyInfo)
            return

        if message.startswith("AllMyInfo"):
            if message.startswith("AllMyInfoAndYou") or self.lvl == 0:
                self.next_move.append("Broadcast AllMyInfo_" + str(self.id) + "_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.inventory["linemate"]) + "_" + str(self.inventory["deraumere"]) + "_" + str(self.inventory["sibur"]) + "_" + str(self.inventory["mendiane"]) + "_" + str(self.inventory["phiras"]) + "_" + str(self.inventory["thystame"]))
            message = message.split("_")
            if len(message) != 10:
                Logger.log_err("AllMyInfo message too short ->" + str(message) , self.id)
                return
            new_player = {
                "id": int(message[1]),
                "orientation": int(orientation),
                "lvl": int(message[2]),
                "food": int(message[3]),
                "linemate": int(message[4]),
                "deraumere": int(message[5]),
                "sibur": int(message[6]),
                "mendiane": int(message[7]),
                "phiras": int(message[8]),
                "thystame": int(message[9])
            }
            if new_player["lvl"] == self.lvl:
                is_in = False
                for player in self.shared_inventory_my_level:
                    if player["id"] == new_player["id"]:
                        player = new_player
                        is_in = True
                        break
                if not is_in:
                    self.shared_inventory_my_level.append(new_player)
                Logger.log_warn("Shared inventory my level : " + str(self.shared_inventory_my_level), self.id)
            Logger.log_warn("AllMyInfo : " + str(new_player))
            for player in self.players:
                if player["id"] == new_player["id"]:
                    player = new_player
                    Logger.log_warn("All players : " + str(self.players), self.id)
                    return
            self.players.append(new_player)
            Logger.log_warn("All players : " + str(self.players), self.id)
            return

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
                self.shared_inventory_my_level = []
                self.lvl = int(response.split(" ")[2])
                self.next_move.append("Broadcast AllMyInfoAndYou_" + str(self.id) + "_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.inventory["linemate"]) + "_" + str(self.inventory["deraumere"]) + "_" + str(self.inventory["sibur"]) + "_" + str(self.inventory["mendiane"]) + "_" + str(self.inventory["phiras"]) + "_" + str(self.inventory["thystame"]))
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
                Logger.log_info("receve type inventory", self.id)
                self.message_type_received.append(TypeResponse.INVENTORY)
                new_inventory = {}
                for i in range(len(response)):
                    if len(response[i]) == 2:
                        new_inventory[response[i][0]] = int(response[i][1])
                    else:
                        Logger.log_err("inventory error |" + str(response[i]) + "|", self.id)
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
                    # self.broadcast(update_inventory)
                return
            self.message_type_received.append(TypeResponse.LOOK)
            Logger.log_info("receve type look", self.id)
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
        Logger.log_send("Look", self.id)
        self.server.send("Look\n")
        self.current_action = "LOOK"
        Logger.log_info("await look", self.id)
        self.data_awaited += 1
        # while self.data_received < self.data_awaited:
        #     pass
        # Logger.log_debug("data_awaited (look) = " + str(self.data_awaited) + " recv = " + str(self.data_received), self.id)

    def forward(self) -> str:
        Logger.log_send("Forward", self.id)
        self.server.send("Forward\n")
        self.current_action = "FORWARD"
        self.boolean_awaited += 1
        # while self.boolean_received < self.boolean_awaited:
        #     pass

    def right(self) -> str:
        Logger.log_send("Right", self.id)
        self.server.send("Right\n")
        self.current_action = "RIGHT"
        self.boolean_awaited += 1
        # while self.boolean_received < self.boolean_awaited:
        #     pass

    def left(self) -> str:
        Logger.log_send("Left", self.id)
        self.server.send("Left\n")
        self.current_action = "LEFT"
        self.boolean_awaited += 1
        # while self.boolean_received < self.boolean_awaited:
        #     pass

    def getInventory(self):
        Logger.log_send("inventory", self.id)
        self.server.send("Inventory\n")
        self.current_action = "INVENTORY"
        self.data_awaited += 1
        while self.data_received < self.data_awaited:
            pass
        Logger.log_debug("inventory receve", self.id)

    def broadcast(self, message):
        # uncrypt message
        Logger.log_send("Broadcast: " + message, self.id)
        message = ''.join(chr(ord(a) ^ 1) for a in message)
        self.server.send(("Broadcast " + message + "\n"))
        self.current_action = "BROADCAST"
        self.boolean_awaited += 1
        # can only send ok
        # while self.boolean_received < self.boolean_awaited:
        #     pass
        # Logger.log_debug("broadcast receve", self.id)

    def connect_nbr(self):
        self.server.send("Connect_nbr\n")
        self.current_action = "CONNECT_NBR"

    def fork(self, data: dict):
        Logger.log_send("fork", self.id)
        self.server.send("Fork\n")
        self.current_action = "FORK"
        subprocess.Popen(["./zappy_ai", "-p", str(data["port"]), "-n", str(data["team_name"]), "-h", str(data["host"])])
        self.forked_nbr += 1
        self.boolean_awaited += 1
        # can only send ok
        # while self.boolean_received < self.boolean_awaited:
        #     pass
        # Logger.log_debug("fork receve", self.id)
        # if self.message_received[-1] != "ok":
        #     Logger.log_err("!!!! fork error, recve " + str(self.message_received[-1]) , self.id)

    def eject(self):
        self.server.send("Eject\n")
        self.current_action = "EJECT"
        self.boolean_awaited += 1
        Logger.log_debug("boolean_awaited (eject) = " + str(self.boolean_awaited) + " recv = " + str(self.boolean_received), self.id)
        # return self.response

    def take(self, object):
        Logger.log_send("take " + object, self.id)
        self.server.send(("Take " + object + "\n"))
        self.current_action = "TAKE"
        self.boolean_awaited += 1
        while self.boolean_received < self.boolean_awaited:
            pass
        Logger.log_debug("take receve: " + str(self.message_received[-1]), self.id)
        if self.message_received[-1] == "ok":
            self.inventory[object] += 1
            Logger.log_info("inventory " + str(self.inventory), self.id)
        else:
            Logger.log_err("take error, no " + object + " on the ground because receve " + self.message_received[-1], self.id)

    def set(self, object):
        Logger.log_send("set " + object, self.id)
        self.server.send(("Set " + object + "\n"))
        self.current_action = "SET"
        self.boolean_awaited += 1
        while self.boolean_received < self.boolean_awaited:
            pass
        Logger.log_debug("set receve", self.id)
        if self.message_received[-1] == "ok":
            self.inventory[object] -= 1
            # Logger.log_debug("set " + object + " success", self.id)
        else:
            Logger.log_err("set error, no " + object + " in inventory because receve " + self.message_received[-1], self.id)
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
        # self.getInventory()
        # self.look()
        self.drop_stone()
        # while self.boolean_received < self.boolean_awaited:
        #     pass
        self.boolean_awaited += 1
        self.current_action = "INCANTATION"
        Logger.log_send("incantation", self.id)
        self.server.send("Incantation\n")
        while self.boolean_received < self.boolean_awaited:
            pass
        # check with last response if incantation is ok
        Logger.log_debug("incantation receve", self.id)
        if self.message_received[-1] == "ko":
            # self.boolean_awaited += 1
            Logger.log_err("incantation ko", self.id)
            self.look()
            Logger.log_err("is there enought ?", self.id)
        else:
            Logger.log_success("message received = " + str(self.message_received[-1]), self.id)
            Logger.log_success("player " + str(self.id) + " level up to " + str(self.lvl), self.id)
