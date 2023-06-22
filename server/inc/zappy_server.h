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
#include <time.h>
#include <fcntl.h>

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
#include "my_tuple.h"

#define FOOD_TIME 126

#define RESSOURCES_RESPAWN_TIME 20

#define MAX_WIDTH 30
#define MIN_WIDTH 10

#define MAX_HEIGHT 30
#define MIN_HEIGHT 10

#define MAX_CLIENTS_NB 1000
#define MIN_CLIENTS_NB 1

#define MAX_FREQ 10000
#define MIN_FREQ 1

#define MAX_TEAMS_NB 100
#define MIN_TEAMS_NB 1

#define MAX_PORT 65535
#define MIN_PORT 1025

#define HATCH_TIME 600

struct base_type_s {
    int _int;
    char _char;
    float _float;
    double _double;
};

struct arg_s {
    int port;
    int width;
    int height;
    struct my_vector_s *names;
    int *team_slots_server;
    int clientsNb;
    int freq;
};

struct server_s {
    int server_sock;
    struct sockaddr_in server_addr;
};

struct incant_s {
    int level;
    int nb_players;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
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

struct egg_s {
    int id;
    int posx;
    int posy;
    int hatch_time;
    bool is_hatched;
    bool is_forked;
    enum orientation_e orientation;
    struct my_string_s *team;
};

struct global_struct_s;

struct network_client_s {
    int client_fd;
    struct my_string_s *buffer;
};

struct client_s {
    struct network_client_s *network_client;
    bool is_closed;
    bool is_gui;
    struct my_string_s *team;
    int posx;
    int posy;
    enum orientation_e orientation;
    int client_nb;
    int food_time;
    int time;
    void (*exec)(struct global_struct_s *g, struct client_s *client,
        struct my_string_s *buffer);
    struct my_string_s *cmd;
    int is_incanting;
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
    struct my_vector_s *eggs;
    struct my_vector_s *incant_need;
    int ressources_respawn;
    int client_id;
    int egg_id;
    int ai_spawn;
    int maxfd;
    fd_set readset;
    fd_set writeset;
    struct timeval timeout;
    bool null_timeout;
    int lowest_time;
};

// Getter
struct global_struct_s *get_global_struct(void);

// Connect command
void command_gui_graphic(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_team(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer, struct my_string_s *name);

// GUI command
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
void command_ai_fork(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_eject(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_take(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_set(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);
void command_ai_incantation_start(struct global_struct_s *g,
struct client_s *client, struct my_string_s *buffer);
void command_ai_incantation_end(struct global_struct_s *g,
struct client_s *client, struct my_string_s *buffer);

// Ressources respawn
void ressoure_respawn(void);

// Initializer
void initialize_map(void);
void initialize_server(void);

// Utils
void convert_coordinate(int *x, int *y);
void send_to_all_gui(struct global_struct_s *global_struct, char *msg);
void send_to_client(struct client_s *client, char *format, ...);

// Arg management
void check_args(int ac, char **av);

// Client management
void client_disconnection(struct client_s *client, struct global_struct_s *g);
void accept_new_client(int select_result, struct global_struct_s *g);
bool ai_starve_eat(struct global_struct_s *g, struct client_s *client);
void manage_clients(int select_result, struct global_struct_s *g);

// Command management
void manage_command(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer);

// Memory management
void free_all(void);
void close_client(void);
void sigint_handler(int sig);

// Main function
int zappy_server(int ac, char **av);
