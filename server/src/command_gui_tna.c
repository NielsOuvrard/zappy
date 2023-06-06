/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_tna(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui == false || client->team == NULL)
        return;
    for (int i = 0; i < vector_length(g->arg->names); i++)
        dprintf(client->client_fd, "tna %s\n",
        ((struct my_string_s *)vector_get(g->arg->names, i))->str);
}
