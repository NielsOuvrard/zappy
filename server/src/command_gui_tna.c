/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_gui_tna(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    for (int i = 0; i < vector_length(g->arg->names); i++)
        send_to_client(client, "tna %s\n",
        ((struct my_string_s *)vector_get(g->arg->names, i))->str);
}
