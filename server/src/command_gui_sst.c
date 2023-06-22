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
    struct my_vector_s *args = string_split(buffer, " ");
    if (vector_length(args) != 2)
        return;
    int value = atoi(((struct my_string_s *)vector_get(args, 1))->str);
    g->arg->freq = value;
    send_to_client(client, "sst %d\n", g->arg->freq);
    vector_set_destructor(args, string_destroy);
    vector_destroy(args);
}
