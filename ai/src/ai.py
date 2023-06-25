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

from enum import Enum

class TypeResponse(Enum):
    BOOL = 0
    INVENTORY = 1
    LOOK = 2
    BROADCAST = 3

def thread_function(player: Player):
    while (player.iamdead == False):
        player.manage_response()



def main():
    data: dict = setup_data()
    player: Player = connect_to_server(data)

    response_manager = threading.Thread(target=thread_function, args=(player,))
    response_manager.start()

    player.broadcast("Hello")

    while (player.iamdead == False):
        player.look()
        player.getInventory()

        if player.next_move == []:
            # * food / stone / reproduction / incantation / Gather
            player.compute_priority()
            Logger.log_prio("priority : " + str(player.priority), player.id)
            if not player.need_to_gather():
                on_the_good_tile_to_act = True
                if player.need_to_move():
                    on_the_good_tile_to_act = player.find_next_move_with_priority()
                if on_the_good_tile_to_act:
                    player.compute_action()

        if player.next_move != []:
            Logger.log_warn("next_move : " + str(player.next_move), player.id)
            while player.next_move != []:
                if player.iamdead:
                    sys.exit(0)
                action: str = player.next_move.pop(0)
                if action == "Forward":
                    player.forward()
                elif action == "Left":
                    player.left()
                elif action == "Right":
                    player.right()
                elif action == "Incantation":
                    player.incantation()
                elif action == "Fork":
                    player.fork(data)
                elif action.startswith("Broadcast"):
                    messsage = action.split(" ")[0]
                    player.broadcast(action[len(messsage) + 1:])
                else:
                    player.take(action)
            # sleep(0.3)
    sys.exit(0)

if __name__ == "__main__":
    main()
