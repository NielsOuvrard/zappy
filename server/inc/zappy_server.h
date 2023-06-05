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

#include "my_vector.h"
#include "my_string.h"

struct arg_s {
    int port;
    int width;
    int height;
    struct vector_s *names;
    int clientsNb;
    int freq;
};

struct global_struct_s {
    struct arg_s *arg;
    struct vector_s *map;
};

struct arg_s *get_arg(void);
struct global_struct_s *get_global_struct(void);

int zappy_server(int ac, char **av);
