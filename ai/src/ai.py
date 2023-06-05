##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## ai
##

import socket
import sys
from parse_arg import setup_data

data = setup_data()

print(data)
sys.exit(0)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('localhost', 4242))

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

