##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## main
##

import random
import socket
import sys
import threading
import json
from time import sleep

from parse_arg import setup_data
from character import Player
from network import Network
from logger import Logger

# One unit of food allows them to live for 126 units of time

# It is not necessary for the players to be on the same team; they only need to be of the same level

# the client sends the "look" command
# receives :
# [ player , object-on-tile1 , ... , object-on-tileP ,...]


# sond transmission
# perceive : the direction the sound + subsequent message.

# In the beginning of the game, a team has n slot available
# # (represented on the board by an egg waiting for a client to connect).
# so...

def connect_to_server(data):
    server = Network(data)

    response = server.recv() # WELCOME\n
    server.send(data["team_name"] + "\n")
    response = server.recv()

    if response == "ko\n":
        Logger.log_err("Error: Invalid team name")
        sys.exit(84)

    size_x = 0
    size_y = 0
    response = server.recv()
    if response == "ko\n":
        Logger.log_err("Error: Invalid map size")
        sys.exit(84)
    else:
        size_x = int(response.split(" ")[0])
        size_y = int(response.split(" ")[1])

    player = Player(size_x, size_y, 0, server)
    return player

# 1
# 4
# 9
# 16
# 25

# take -> getInventory
# difference between old and new inventory -> shared_inventory

# issue [AI] Handle map
# def fill_map(player: Player, look: list, size: int, incr: int = 1):
#     for i in range(size):
#         player.map.append(look[i]) # to change
#     if look.length() > size:
#         fill_map(player, look[size:], size + incr, incr + 2)

from enum import Enum

class TypeResponse(Enum):
    BOOL = 0
    INVENTORY = 1
    LOOK = 2
    BROADCAST = 3

def thread_function(player: Player):
    while (1):
        player.manage_response()

def main():
    data: dict = setup_data()
    player: Player = connect_to_server(data)

    response_manager = threading.Thread(target=thread_function, args=(player,))
    response_manager.start()

    player.broadcast("Hello")

    # player.manage_response()

    while (1):
        player.look()
        player.getInventory()
        # input()
        if player.next_move == []:
            player.compute_good_case()
            player.compute_action()
        else:
            while player.next_move != []:
                # Logger.log_warn("next_move : " + str(player.next_move), player.id)
                action: str = player.next_move.pop(0)
                if action == "Forward":
                    player.forward()
                elif action == "Left":
                    player.left()
                elif action == "Right":
                    player.right()
                elif action == "Incantation":
                    Logger.log_warn("Incantation", player.id)
                    player.incantation()
                elif action == "Fork":
                    Logger.log_warn("Fork", player.id)
                    player.fork(data)
                    player.broadcast("")
                elif action.startswith("Broadcast"):
                    # Logger.log_send("Broadcast", player.id)
                    messsage = action.split(" ")[0]
                    player.broadcast(action[len(messsage) + 1:])
                else:
                    # Logger.log_warn("take " + action, player.id)
                    player.take(action)
                    player.getInventory()
                sleep(0.04)
                    # if res_take == "ok" and action != "food":
                    #     Logger.log_info("take " + action, player.id)
                    #     player.inventory[action] += 1
                    #     player.shared_inventory[action] += 1
                    #     player.broadcast("SharedInventory_" + action + "_" + str(player.shared_inventory[action]))
                    #     Logger.log_warn("shared_inventory : " + str(player.shared_inventory), player.id)
                    #     Logger.log_warn("inventory : " + str(player.inventory), player.id)
                    # elif res_take == "ko":
                    #     Logger.log_err("take " + action, player.id)
        # response = player.server.recv(1024).decode()
        # player.parse_cmd(response)
        # command = player.next_command[0]
        # player.getInventory()
        # if player.getInventory() == "dead":
        #     break

        # if simple_algo_eat(player):
        #     res = player.take("food")
    sys.exit(0)

if __name__ == "__main__":
    main()
