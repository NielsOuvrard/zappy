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
#include <errno.h>

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <limits.h>
#include <sys/stat.h>

#include "my_vector.h"
#include "my_string.h"

struct arg_s {
    int port;
    int width;
    int height;
    struct my_vector_s *names;
    int clientsNb;
    int freq;
};

struct server_s {
    int server_sock;
    struct sockaddr_in server_addr;
};

struct client_s {
    bool is_closed;
    bool is_gui;
    int client_fd;
};

struct global_struct_s {
    struct arg_s *arg;
    struct my_vector_s *map;
    struct server_s *server;
    struct my_vector_s *clients;
    int maxfd;
    fd_set readset;
    fd_set writeset;
};

struct global_struct_s *get_global_struct(void);

void initialize_map(void);
void initialize_server(void);

int zappy_server(int ac, char **av);
