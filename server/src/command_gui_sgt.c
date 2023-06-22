/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_gui_sgt(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    send_to_client(client, "sgt %d\n", g->arg->freq);
}
