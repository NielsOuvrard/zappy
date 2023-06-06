/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_gui_sst(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui == false || client->team == NULL)
        return;
    struct my_vector_s *args = string_split(buffer, " ");
    if (vector_length(args) != 2)
        return;
    int value = atoi(((struct my_string_s *)vector_get(args, 1))->str);
    g->arg->freq = value;
    dprintf(client->client_fd, "sst %d\n", g->arg->freq);
}
