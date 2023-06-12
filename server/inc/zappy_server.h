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
#include <signal.h>
#include <math.h>

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
#include "my_map.h"

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

struct tile_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};

enum orientation_e {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

struct client_s {
    bool is_closed;
    bool is_gui;
    int client_fd;
    struct my_string_s *buffer;
    struct my_string_s *team;
    int posx;
    int posy;
    enum orientation_e orientation;
    int client_nb;
    int level;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};

struct global_struct_s {
    struct arg_s *arg;
    struct my_vector_s *map;
    struct server_s *server;
    struct my_vector_s *clients;
    struct my_map_s *team_slots;
    int client_id;
    int ai_spawn;
    int maxfd;
    fd_set readset;
    fd_set writeset;
};

// Getter
struct global_struct_s *get_global_struct(void);

// GUI command
void command_gui_graphic(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_msz(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_bct(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_mct(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_tna(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_ppo(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_plv(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_pin(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_sgt(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_gui_sst(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);

// AI command
void command_ai_team(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer, struct my_string_s *name);
void command_ai_forward(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_right(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_left(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_look(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_inventory(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_broadcast(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_connect_nbr(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);

void command_ai_take(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);

// Initializer
void initialize_map(void);
void initialize_server(void);

// Utils
void convert_coordinate(int *x, int *y);

// Main function
int zappy_server(int ac, char **av);
