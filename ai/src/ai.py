##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## main
##

import random
import socket
import sys
import json

from parse_arg import setup_data
from character import Player

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
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.connect((data["host"], data["port"]))
    except ConnectionRefusedError:
        print("Error: Connection refused to: " + data["host"] + ":" + str(data["port"]))
        sys.exit(84)

    response = server.recv(1024).decode() # WELCOME\n
    server.send((data["team_name"] + "\n").encode())
    response = server.recv(1024).decode()
    print("recieve '" + response + "'")

    if response == "ko\n":
        print("Error: Invalid team name")
        sys.exit(84)
    lines = response.split("\n")
    id = int(response.split("\n")[0])

    size_x = 0
    size_y = 0
    if len(lines) >= 2 and lines[1] != "":
        size_x = int(response.split("\n")[1].split(" ")[0])
        size_y = int(response.split("\n")[1].split(" ")[1])
    else:
        response = server.recv(1024).decode()
        if response == "ko\n":
            print("Error: Invalid team name")
            sys.exit(84)
        size_x = int(response.split("\n")[0].split(" ")[0])
        size_y = int(response.split("\n")[0].split(" ")[1])

    player = Player(size_x, size_y, id, server)
    return player

# 1
# 4
# 9
# 16
# 25

# issue [AI] Handle map
# def fill_map(player: Player, look: list, size: int, incr: int = 1):
#     for i in range(size):
#         player.map.append(look[i]) # to change
#     if look.length() > size:
#         fill_map(player, look[size:], size + incr, incr + 2)

def check_food(player: Player, look: list):
    if len(look) <= 2:
        return False
    for thing in look[2]:
        if thing == "food":
            return True
    return False


def simple_algo_eat(player: Player):
    look: list = player.look()
    for thing in look[0]:
        if thing == "food":
            return 1
    for i in range(4):
        look: list = player.look()
        if check_food(player, look):
            res = player.forward()
            print("forward", res)
            return 1
        res = player.right()
        print("right", res)
    val_rand = random.randint(0, 2)
    if val_rand == 0:
        res = player.right()
        print("right", res)
    elif val_rand == 1:
        res = player.left()
        print("left", res)
    else:
        res = player.forward()
        print("forward", res)
    return 0

def detect_priority(player: Player, look: list):
    """
    Detect priority of the looked ressources
    """

def main():
    data = setup_data()
    player = connect_to_server(data)
    print("inventory", player.inventory)

    while (1):
        # input()
        player.getInventory()
        print("inventory", player.inventory)
        player.look()
        # print("map", json.dumps(player.map, indent=4))
        print("PLAYER STATE", player.priority)
        if player.next_move == []:
            player.compute_good_case()
            player.compute_action()
        else:
            while player.next_move != []:
                action = player.next_move.pop(0)
                print("action TO DO", action)
                if action == "Forward":
                    player.forward()
                elif action == "Left":
                    player.left()
                elif action == "Right":
                    player.right()
                elif action == "Incantation":
                    player.incantation()
                else:
                    player.take(action)
        # response = player.server.recv(1024).decode()
        # player.parse_cmd(response)
        # command = player.next_command[0]
        # print("command = ", command)
        # player.getInventory()
        # if player.getInventory() == "dead":
        #     print("player is dead")
        #     break
        # print("inventory", player.getInventory())

        # if simple_algo_eat(player):
        #     res = player.take("food")
        #     print("take food", res)
    sys.exit(0)

if __name__ == "__main__":
    main()
