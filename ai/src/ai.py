##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## ai
##

import socket
import sys
from time import sleep
from parse_arg import setup_data


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

def main():
    data = setup_data()
    # data["team_name"]
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

    # recive :
    # nmb_authorized_remaining_clients_in_team size_x size_y
    nmb_authorized_remaining_clients_in_team = int(response.split("\n")[0])
    size_x = int(response.split("\n")[1].split(" ")[0])
    size_y = int(response.split("\n")[1].split(" ")[1])
    # [ player food deraumere, food food food linemate phiras, food food food linemate mendiane, food deraumere ]

    # server.send("Fordward\n".encode())
    server.send("Look\n".encode())
    response = server.recv(1024).decode()
    print("'" + response + "'")

    while (1):
        response = server.recv(1024).decode()
        print("'" + response + "'")
        message = input("Enter a message to send to the server: ")
        if (message != ""):
            server.send(message.encode())
        if (message == "exit"):
            break
    sys.exit(0)

if __name__ == "__main__":
    main()
