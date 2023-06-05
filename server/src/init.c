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
    global_struct->map = vector_create(sizeof(struct my_vector_s *));
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_create(sizeof(struct my_string_s *));
        for (int j = 0; j < arg->width; j++) {
            vector_push_back(line, string_from_string("X"));
        }
        vector_push_back(global_struct->map, line);
    }
    // print the map
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_get(global_struct->map, i);
        for (int j = 0; j < arg->width; j++) {
            struct my_string_s *str = vector_get(line, j);
            string_print(str);
        }
        printf("\n");
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
