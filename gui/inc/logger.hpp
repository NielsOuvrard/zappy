/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** logger
*/

#pragma once

#define ENABLE_LOG true

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#if ENABLE_LOG == true
#define LOG(COLOR, WHAT, MSG) "[" << COLOR << #WHAT << RESET << "] " << MSG << std::endl
#else
#define LOG(COLOR, WHAT, MSG) ""
#endif

#define LOG_GUI(MSG) LOG(GREEN, GUI, MSG)
#define LOG_ERR_GUI(MSG) LOG(RED, GUI, MSG)

#define LOG_NETWORK(MSG) LOG(YELLOW, NETWORK, MSG)
#define LOG_ERR_NETWORK(MSG) LOG(RED, NETWORK, MSG)

#define LOG_ZAPPY(MSG) LOG(BLUE, ZAPPY, MSG)
#define LOG_ERR_ZAPPY(MSG) LOG(RED, ZAPPY, MSG)