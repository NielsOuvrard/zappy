#!/usr/bin/env python3

import socket
import sys

args: list[str] = sys.argv
args.pop(0)

data: dict = {
    "name": "AI",
    "team-name": args
}

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

# if __name__ == '__main__':
#     inp = input("Press enter to send a message to the server")
#     send_message(inp)
