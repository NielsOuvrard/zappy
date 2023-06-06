##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## parse_arg
##

import sys

def print_help(exit_code):
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")
    sys.exit(exit_code)

def setup_data():
    args = sys.argv
    args.pop(0)
    if (args[0] == "-help" or args[0] == "-h"):
        print_help(0)

    if (len(args) != 6 and len(args) != 4):
        print("Error: Invalid number of arguments")
        print_help(84)

    data: dict = {}
    data["host"] = "localhost"

    for i in range(0, len(args), 2):
        if args[i] == "-n":
            data["team_name"] = args[i + 1]
        elif args[i] == "-p":
            data["port"] = int(args[i + 1])
        elif args[i] == "-h":
            data["host"] = args[i + 1]
        else:
            print("Error: Invalid argument")
            print_help(84)
    return data
