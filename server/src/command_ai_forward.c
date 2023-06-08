/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_forward(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui || client->team == NULL) {
        dprintf(client->client_fd, "suc\n");
        return;
    }
    if (client->orientation == NORTH)
        client->posy = (client->posy - 1 + g->arg->height) % g->arg->height;
    else if (client->orientation == SOUTH)
        client->posy = (client->posy + 1) % g->arg->height;
    else if (client->orientation == EAST)
        client->posx = (client->posx + 1) % g->arg->width;
    else if (client->orientation == WEST)
        client->posx = (client->posx - 1 + g->arg->width) % g->arg->width;
    dprintf(client->client_fd, "ok\n");
}
