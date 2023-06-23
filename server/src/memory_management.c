/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void free_eggs(struct global_struct_s *global_struct)
{
    for (int i = 0; i < vector_length(global_struct->eggs); i++) {
        struct egg_s *egg = vector_get(global_struct->eggs, i);
        string_destroy(egg->team);
        free(egg);
    }
    vector_destroy(global_struct->eggs);
}

void free_all(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    free(arg->team_slots_server);
    vector_destroy(arg->names);
    for (int i = 0; i < vector_length(global_struct->map); i++)
        vector_destroy(vector_get(global_struct->map, i));
    vector_destroy(global_struct->map);
    for (int i = 0; i < vector_length(global_struct->clients); i++) {
        struct client_s *client = vector_get(global_struct->clients, i);
        string_destroy(client->buffer);
        (client->team) ? string_destroy(client->team) : 0;
        (client->cmd) ? string_destroy(client->cmd) : 0;
        if (fcntl(client->client_fd, F_GETFD) != -1) {
            if (!client->is_gui)
                dprintf(client->client_fd, "dead\n");
            close(client->client_fd);
        }
        free(client);
    }
    vector_destroy(global_struct->clients);
    map_destroy(global_struct->team_slots);
    free_eggs(global_struct);
    vector_destroy(global_struct->incant_need);
    free(global_struct->arg);
    free(global_struct->server);
}

void close_client(void)
{
    struct global_struct_s *g = get_global_struct();
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed) {
            struct client_s *tmp = vector_remove(g->clients, i);
            i--;
            string_destroy(tmp->buffer);
            (tmp->team) ? string_destroy(tmp->team) : 0;
            (tmp->cmd) ? string_destroy(tmp->cmd) : 0;
            free(tmp);
        }
    }
}

void sigint_handler(int sig)
{
    (void) sig;
    free_all();
    exit(0);
}
