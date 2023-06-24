##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-kenan.blasius
## File description:
## logger
##

COL_END = '\033[0m'
COL_BLUE = '\033[94m'
COL_CYAN = '\033[96m'
COL_GREEN = '\033[92m'
COL_RED = '\033[91m'
COL_YELLOW = '\033[93m'
COL_WHITE = '\033[97m'
COL_MAGENTA = '\033[95m'
COL_BLACK = '\033[90m'
COL_GREY = '\033[90m'
COL_BOLD = '\033[1m'
COL_UNDERLINE = '\033[4m'

# todo sometimes send data -1
# why take miss
# a command "how many player with level x" / "who's alive"
# why incantation miss

# shared inventory by player with level
# if inv enough -> send food -> player with most food await others in his tile

# * nmb of player with level

class Logger:
    def log_err(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_RED + "ERROR" + COL_END + "] ", msg)
        else:
            print("[" + COL_RED + "ERROR" + COL_END + "] ", msg)

    def log_prio(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_BLUE + "PRIORITY" + COL_END + "] ", msg)
        else:
            print("[" + COL_BLUE + "PRIORITY" + COL_END + "] ", msg)

    def log_warn(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_YELLOW + "WARN" + COL_END + "] ", msg)
        else:
            print("[" + COL_YELLOW + "WARN" + COL_END + "] ", msg)

    def log_info(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_BLUE + "INFO" + COL_END + "] ", msg)
        else:
            print("[" + COL_BLUE + "INFO" + COL_END + "] ", msg)

    def log_debug(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_CYAN + "DEBUG" + COL_END + "] ", msg)
        else:
            print("[" + COL_CYAN + "DEBUG" + COL_END + "] ", msg)

    def log_success(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_GREEN + "SUCCESS" + COL_END + "] ", msg)
        else:
            print("[" + COL_GREEN + "SUCCESS" + COL_END + "] ", msg)

    def log_recve(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_MAGENTA + "RECV" + COL_END + "] ", msg)
        else:
            print("[" + COL_MAGENTA + "RECV" + COL_END + "] ", msg)

    def log_send(msg, id = -1):
        if id != -1:
            print(id, "[" + COL_GREY + "SEND" + COL_END + "] ", msg)
        else:
            print("[" + COL_GREY + "SEND" + COL_END + "] ", msg)
