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
        self.priority = Priority.Undefined
        self.forked_nbr = 0
        self.message_received: list = []
        self.message_type_received: list = []
        self.current_action = "NONE"
        self.players: dict = []
        self.my_level_players: list = []
        self.player_to_gather = None
        self.players_gather_to_me = True
        self.iamdead = False

        # new algo
        self.wait_players = False
        self.follow_player = False
        self.find_player_to_gather = False
        self.players_ready_to_incant = 1 # or put 0 and + 1 when enough stones
        self.main_player_incantation = False

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

    def compute_needed_food(self) -> int:
        """
        Compute the needed food according to the number of foods in the inventory and level
        """
        return (self.go_case_id // 2) + 5

    def share_inventory_my_level(self):
        """
        Share the inventory of the player with the other players of the same level
        """
        inventory = self.inventory.copy()
        if self.lvl == 1:
            return self.inventory
        for player in self.my_level_players:
            inventory["linemate"]   += player["linemate"]
            inventory["deraumere"]  += player["deraumere"]
            inventory["sibur"]      += player["sibur"]
            inventory["mendiane"]   += player["mendiane"]
            inventory["phiras"]     += player["phiras"]
            inventory["thystame"]   += player["thystame"]
        return inventory

    def get_stone(self):
        """
        This function compute the next action to do to get the stone
        """
        needed_stones: dict = self.level_cap[self.lvl - 1].copy()
        needed_stones.pop("ally")
        shared_inv = self.share_inventory_my_level()
        for stone in needed_stones:
            if shared_inv[stone] < needed_stones[stone]:
                return stone
        return None

    def check_incantable_and_hungry(self) -> bool:
        """
        This function check if the player is incantable and hungry
        """
        if not self.get_stone() != None:
            return False
        if self.inventory["food"] < 6:
            self.priority = Priority.Food
        return True

    def need_to_gather(self) -> bool:
        """
        This function check if the player need to gather
        """
        if self.priority == Priority.Gather:
            return True
        return False

    def need_to_move(self) -> bool:
        """
        This function check if the player need to move
        """
        if self.priority == Priority.Reproduction or self.priority == Priority.Incantation:
            return False
        return True

    # * ######################################################################################### PRIORITIES #####################################################################################################
    def compute_priority(self):
        """
        This function compute the priority of the player
        """
        if self.lvl == 8:
            Logger.log_success("Player " + str(self.id) + " is lvl 8")
            # do anything else
            return

        if len(self.map) == 0: # error no map
            self.priority = Priority.Food
            Logger.log_err("Player map is empty", self.id)
            return

        if self.inventory["food"] < 6:
            self.priority = Priority.Food
            return

        if self.lvl == 1 and self.map[0]["linemate"] >= 1:
            self.priority = Priority.Incantation
            return

        if (self.wait_players or self.follow_player) and self.get_stone() == None:
            self.priority = Priority.Gather
            return

        if len(self.players) < self.level_cap[self.lvl - 1]["ally"] - 1:
            self.priority = Priority.Reproduction
            return

        if self.get_stone() != None:
            self.priority = Priority.Stones
            return

        if len(self.my_level_players) < self.level_cap[self.lvl - 1]["ally"] - 1:
            self.priority = Priority.Food
            return

        elif self.get_stone() == None and len(self.my_level_players) >= self.level_cap[self.lvl - 1]["ally"] - 1:
            self.priority = Priority.Gather
            # todo: Am I self.wait_players or self.follow_player
            return
        Logger.log_err("Priority not found", self.id)
        self.priority = Priority.Food
        return

    # todo shortest path
    def find_and_compute_good_case(self):
        """
        According to the map, this function compute the best case to go
        """
        needed_stones = None
        if self.priority == Priority.Stones:
            needed_stones = self.get_stone()
        self.go_case_id = -1

        if self.map[0]["food"] > 0 and self.priority == Priority.Food:
            self.go_case_id = 0
            return
        if self.map[0][needed_stones] > 0:
            self.go_case_id = 0
            return

        for i in range(1, len(self.map), 1):
            if self.priority == Priority.Food and self.map[i]["food"] > 0:
                self.go_case_id = i
                return
            elif needed_stones != None and self.map[i][needed_stones] > 0:
                self.go_case_id = i
                return
        Logger.log_err("No case found", self.id)
        return

    def go_to_case(self):
        """
        This function compute the next action to do to go to the case
        """
        # todo: put it somewhere else
        Logger.log_warn("go to case " + str(self.go_case_id), self.id)
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
            return
        # forward after turn
        mov = 0
        while mov < abs(x):
            self.next_move.append("Forward")
            mov += 1
        Logger.log_warn("so we do " + str(self.next_move) + "\n", self.id)
        return

    def where_move_to_gather(self, orientation: int):
        """
        This function compute the next action to do to go to the case
        """
        Logger.log_prio("gather to: " + str(orientation), self.id)
        if orientation == 0:
            # your orientation is the same as the player
            # wait until enough player to incant
            return
        elif orientation == 1:
            self.next_move.append("Forward")
        elif orientation == 2:
            self.next_move.append("Forward")
            self.next_move.append("Left")
            self.next_move.append("Forward")
        elif orientation == 3:
            self.next_move.append("Left")
            self.next_move.append("Forward")
        elif orientation == 4:
            self.next_move.append("Left")
            self.next_move.append("Forward")
            self.next_move.append("Left")
            self.next_move.append("Forward")
        elif orientation == 5:
            self.next_move.append("Left")
            self.next_move.append("Left")
            self.next_move.append("Forward")
        elif orientation == 6:
            self.next_move.append("Right")
            self.next_move.append("Forward")
            self.next_move.append("Right")
            self.next_move.append("Forward")
        elif orientation == 7:
            self.next_move.append("Right")
            self.next_move.append("Forward")
        elif orientation == 8:
            self.next_move.append("Forward")
            self.next_move.append("Right")
            self.next_move.append("Forward")
        # allMyInfo = "AllMyInfoAndLevel_" + str(self.id) + "_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.inventory["linemate"]) + "_" + str(self.inventory["deraumere"]) + "_" + str(self.inventory["sibur"]) + "_" + str(self.inventory["mendiane"]) + "_" + str(self.inventory["phiras"]) + "_" + str(self.inventory["thystame"])
        self.next_move.append("Broadcast WhereAreYou_" + self.player_to_gather["id"])

    # * ######################################################################################### COMPUTE ACTION ######################################################################################### * #

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
        elif self.priority == Priority.Incantation:
            self.next_move.append("Incantation")
        else:
            Logger.log_err("Priority not found, try to take food", self.id)
            self.next_move.append("food")

    # * ######################################################################################### FIND NEXT MOVE ######################################################################################### * #

    def find_next_move_with_priority(self) -> bool:
        """
        fill self.go_case_id and self.next_move
        """
        self.find_and_compute_good_case()

        if self.go_case_id == -1:
            for i in range(self.lvl):
                self.forward()
            return False

        if self.go_case_id == 0:
            return True

        # if not enough food to move to the case
        if self.priority != Priority.Food and self.inventory["food"] < self.compute_needed_food():
            Logger.log_warn("food : " + str(self.inventory["food"]) + " needed to move away: " + str(self.needed_food), self.id)
            self.priority = Priority.Food
            return self.find_next_move_with_priority()

        self.go_to_case()
        return True

    # * ######################################################################################### BRADCAST ####################################################################################################
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
            for player in self.my_level_players: # ? is it a pointer ? does it increment twice ?
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



        if self.follow_player:
            if message.startswith("Incant"):
                message = message.split("_")
                # todo
                # wait until "recv (Level 2)" or "recv (stop)"
                return

            if message.startswith("StopIncant"):
                message = message.split("_")
                if len(message) != 2:
                    Logger.log_err("StopIncant message too short ->" + str(message) , self.id)
                    return
                if int(message[1]) == self.player_to_gather["id"]:
                    self.follow_player = False
                    self.find_player_to_gather = False
                return

            if message.startswith("IAmHere"):
                message = message.split("_")
                if len(message) != 2:
                    Logger.log_err("IAmHere message too short ->" + str(message) , self.id)
                    return
                if orientation == 0:
                    self.find_player_to_gather = True
                    return
                if int(message[1]) == self.player_to_gather["id"]:
                    # ? is that useful ?
                    #  self.player_to_gather["orientation"] = orientation
                    self.where_move_to_gather(orientation) # and Broadcast WhereAreYou_
                return


        elif self.wait_players:
            if message.startswith("WhereAreYou"):
                message = message.split("_")
                if len(message) != 2:
                    Logger.log_err("WhereAreYou message too short ->" + str(message) , self.id)
                    return
                if message[1] == str(self.id):
                    self.next_move.append("Broadcast IAmHere_" + str(self.id))
                    if orientation == 0:
                        self.players_ready_to_incant += 1
                        if self.players_ready_to_incant == self.level_cap[self.lvl - 1]["ally"]:
                            self.wait_players = False
                            self.next_move.append("Broadcast Incant_" + str(self.id))
                        #todo: whrer StopIncant ?
                        # self.next_move.append("Broadcast StopIncant_" + str(self.id))
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
                # add player to my level players
                is_in = False
                for player in self.my_level_players:
                    if player["id"] == new_player["id"]:
                        player = new_player
                        is_in = True
                        break
                if not is_in:
                    self.my_level_players.append(new_player)
                Logger.log_warn("Shared inventory my level : " + str(self.my_level_players), self.id)
            else:
                # remove player from my level players
                for player in self.my_level_players:
                    if player["id"] == new_player["id"]:
                        self.my_level_players.remove(player)
                        break
            Logger.log_warn("AllMyInfo : " + str(new_player))
            for player in self.players:
                if player["id"] == new_player["id"]:
                    player = new_player
                    Logger.log_warn("All players : " + str(self.players), self.id)
                    return
            self.players.append(new_player)
            Logger.log_warn("All players : " + str(self.players), self.id)
            return

    # * ######################################################################################### RESPONSE ####################################################################################################
    def manage_response(self) -> None:
        response = self.server.recv()

        if response == "dead":
            self.iamdead = True
            return

        self.message_received.append(response)
        Logger.log_recve(response, self.id)
        # Logger.log_info("last 3 message received -> " + str(self.message_received[-3:]), self.id)

        if response == "Elevation underway" and self.current_action != "INCANTATION":
            Logger.log_err("Elevation underway but not incantation", self.id)
            return

        elif response.startswith("Current level: "):
            if self.lvl != int(response.split(" ")[2]):
                self.my_level_players = []
                self.lvl = int(response.split(" ")[2])
                self.next_move.append("Broadcast AllMyInfoAndYou_" + str(self.id) + "_" + str(self.lvl) + "_" + str(self.inventory["food"]) + "_" + str(self.inventory["linemate"]) + "_" + str(self.inventory["deraumere"]) + "_" + str(self.inventory["sibur"]) + "_" + str(self.inventory["mendiane"]) + "_" + str(self.inventory["phiras"]) + "_" + str(self.inventory["thystame"]))
                Logger.log_err("lvl up to " + str(self.lvl), self.id)
            else:
                Logger.log_err("lvl up but same lvl", self.id)
                # self.players_not_gather_to_me_but_waiting_incant = False
                # todo set var to false ?
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

    # * ######################################################################################### ACTION ####################################################################################################

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
            if self.lvl > 1 and self.main_player_incantation:
                self.main_player_incantation = False
                self.players_ready = -1
                self.wait_players = False
                self.next_move.append("StopIncant_" + str(self.id))
            # self.boolean_awaited += 1
            Logger.log_err("incantation ko", self.id)
            self.look()
            Logger.log_err("is there enought ?", self.id)
        else:
            Logger.log_success("message received = " + str(self.message_received[-1]), self.id)
            Logger.log_success("player " + str(self.id) + " level up to " + str(self.lvl), self.id)
