/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_eject(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int x = client->posx;
    int y = client->posy;

    bool success = false;
    if (client->orientation == NORTH) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posy = (tmp->posy - 1 + g->arg->height) % g->arg->height;
                dprintf(tmp->client_fd, "eject: %d\n", SOUTH);
                success = true;
            }
        }
    } else if (client->orientation == SOUTH) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posy = (tmp->posy + 1) % g->arg->height;
                dprintf(tmp->client_fd, "eject: %d\n", NORTH);
                success = true;
            }
        }
    } else if (client->orientation == EAST) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posx = (tmp->posx + 1) % g->arg->width;
                dprintf(tmp->client_fd, "eject: %d\n", WEST);
                success = true;
            }
        }
    } else if (client->orientation == WEST) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posx = (tmp->posx - 1 + g->arg->width) % g->arg->width;
                dprintf(tmp->client_fd, "eject: %d\n", EAST);
                success = true;
            }
        }
    }
    if (success)
        dprintf(client->client_fd, "ok\n");
    else
        dprintf(client->client_fd, "ko\n");
}