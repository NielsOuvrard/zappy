/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_right(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui || client->team == NULL) {
        dprintf(client->client_fd, "suc\n");
        return;
    }
    if (client->orientation == NORTH)
        client->orientation = EAST;
    else if (client->orientation == SOUTH)
        client->orientation = WEST;
    else if (client->orientation == EAST)
        client->orientation = SOUTH;
    else if (client->orientation == WEST)
        client->orientation = NORTH;
    dprintf(client->client_fd, "ok\n");
}
