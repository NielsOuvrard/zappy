##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## parse_arg
##

import sys

def setup_data():
    data: dict = {}
    args = sys.argv
    args.pop(0)
    if (args[0] == "-help"):
        print("USAGE: ./zappy_ai -p port -n name -h machine")
        print("\tport\tis the port number")
        print("\tname\tis the name of the team")
        print("\tmachine\tis the name of the machine; localhost by default")
        sys.exit(0)
    if (len(args) % 2 != 0):
        print("Error: Invalid number of arguments")
        sys.exit(84)
    for arg in args:
        if arg == "-n":
            data["team_name"] = args[args.index(arg) + 1]
        elif arg == "-p":
            data["port"] = int(args[args.index(arg) + 1])
        elif arg == "-h":
            data["host"] = args[args.index(arg) + 1]
    if not "-h" in args:
        data["host"] = "localhost"
    return data


