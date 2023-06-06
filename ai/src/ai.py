##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## ai
##

import socket
import sys
from parse_arg import setup_data


# One unit of food allows them to live for 126 units of time

# It is not necessary for the players to be on the same team; they only need to be of the same level


def main():
    data = setup_data()
    print(data)
    # data["team_name"]
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.connect((data["host"], data["port"]))
    except ConnectionRefusedError:
        print("Error: Connection refused to: " + data["host"] + ":" + str(data["port"]))
        sys.exit(84)

    while (1):
        response = server.recv(1024).decode()
        print("'" + response + "'")
        if (response == "WELCOME\n"):
            print("Connected to the server")
            server.send("START\n".encode())
        message = input("Enter a message to send to the server: ")
        if (message != ""):
            server.send(message.encode())
        if (message == "exit"):
            break
    sys.exit(0)

if __name__ == "__main__":
    main()
