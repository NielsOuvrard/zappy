##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## main
##

import random
import socket
import sys
from time import sleep
from parse_arg import setup_data
from Player import Player


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
def fill_map(player: Player, look: list, size: int, incr: int = 1):
    for i in range(size):
        player.map.append(look[i]) # to change
    if look.length() > size:
        fill_map(player, look[size:], size + incr, incr + 2)


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

['player', 'mendiane', 'mendiane', 'linemate', 'food', 'food']
def main():
    data = setup_data()
    player = connect_to_server(data)
    print("inventory", player.inventory())

    while (1):
        inventory: list = player.inventory()
        if len(inventory) == 0:
            print("inventory is empty")
            break
        print("inventory", inventory)
        if simple_algo_eat(player):
            res = player.take("food")
            print("take food", res)
    sys.exit(0)

if __name__ == "__main__":
    main()
