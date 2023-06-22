/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_left(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->orientation == NORTH)
        client->orientation = WEST;
    else if (client->orientation == SOUTH)
        client->orientation = EAST;
    else if (client->orientation == EAST)
        client->orientation = NORTH;
    else if (client->orientation == WEST)
        client->orientation = SOUTH;
    send_to_client(client, "ok\n");
    struct my_string_s *msg = string_from_format("ppo %d %d %d %d\n",
    client->client_nb, client->posx, client->posy, client->orientation);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
}
