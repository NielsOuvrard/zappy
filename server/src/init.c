/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void initialize_map(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    global_struct->client_id = 0;
    global_struct->ai_spawn = false;
    global_struct->map = vector_create(sizeof(struct my_vector_s *));
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_create(sizeof(struct my_string_s *));
        for (int j = 0; j < arg->width; j++) {
            struct tile_s *tile = malloc(sizeof(struct tile_s));
            tile->food = 0;
            tile->linemate = 0;
            tile->deraumere = 0;
            tile->sibur = 0;
            tile->mendiane = 0;
            tile->phiras = 0;
            tile->thystame = 0;
            vector_push_back(line, tile);
        }
        vector_push_back(global_struct->map, line);
    }
    int max_food = (arg->width * arg->height) * 0.5;
    int max_linemate = (arg->width * arg->height) * 0.3;
    int max_deraumere = (arg->width * arg->height) * 0.15;
    int max_sibur = (arg->width * arg->height) * 0.1;
    int max_mendiane = (arg->width * arg->height) * 0.1;
    int max_phiras = (arg->width * arg->height) * 0.08;
    int max_thystame = (arg->width * arg->height) * 0.05;
    int max_all = max_food + max_linemate + max_deraumere +
    max_sibur + max_mendiane + max_phiras + max_thystame;
    while (max_all) {
        int x = rand() % arg->width;
        int y = rand() % arg->height;
        int r = rand() % 7;
        struct tile_s *tile = vector_get(vector_get(global_struct->map, y), x);
        if (r == 0 && max_food > 0 && tile->food <= 0) {
            tile->food++;
            max_food--;
            max_all--;
        }
        if (r == 1 && max_linemate > 0 && tile->linemate <= 0) {
            tile->linemate++;
            max_linemate--;
            max_all--;
        }
        if (r == 2 && max_deraumere > 0 && tile->deraumere <= 0) {
            tile->deraumere++;
            max_deraumere--;
            max_all--;
        }
        if (r == 3 && max_sibur > 0 && tile->sibur <= 0) {
            tile->sibur++;
            max_sibur--;
            max_all--;
        }
        if (r == 4 && max_mendiane > 0 && tile->mendiane <= 0) {
            tile->mendiane++;
            max_mendiane--;
            max_all--;
        }
        if (r == 5 && max_phiras > 0 && tile->phiras <= 0) {
            tile->phiras++;
            max_phiras--;
            max_all--;
        }
        if (r == 6 && max_thystame > 0 && tile->thystame <= 0) {
            tile->thystame++;
            max_thystame--;
            max_all--;
        }
    }
}

void initialize_server(void)
{
    struct global_struct_s *g = get_global_struct();
    struct arg_s *arg = g->arg;
    struct server_s *server = malloc(sizeof(struct server_s));
    server->server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server->server_sock == -1) {
        printf("socket: %s", strerror(errno));
        exit(84);
    }
    server->server_addr = (struct sockaddr_in) {0};
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(arg->port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(server->server_sock, SOL_SOCKET, (SO_REUSEADDR), (char*) &server->server_addr, sizeof(server->server_addr)) == -1)
        exit(84);
    if (bind(server->server_sock, (const struct sockaddr *) &server->server_addr, sizeof(server->server_addr)) == -1) {
        printf("bind: %s", strerror(errno));
        exit(84);
    }
    if (listen(server->server_sock, 1000) == -1) {
        printf("listen: %s", strerror(errno));
        exit(84);
    }
    g->server = server;
}
