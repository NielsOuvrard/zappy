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
from time import sleep
from parse_arg import setup_data
from character import Player


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

    id = int(response.split("\n")[0])
    size_x = int(response.split("\n")[1].split(" ")[0])
    size_y = int(response.split("\n")[1].split(" ")[1])
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
        input()
        if player.first == True:
            player.first = False
            player.look()
        print("inventory", player.inventory)
        print("map", json.dumps(player.map, indent=4))
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
