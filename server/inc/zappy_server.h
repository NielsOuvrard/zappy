/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arg_s {
    int port;
    int width;
    int height;
    char **names;
    int clientsNb;
    int freq;
};

struct arg_s *get_arg(void);

int zappy_server(int ac, char **av);
