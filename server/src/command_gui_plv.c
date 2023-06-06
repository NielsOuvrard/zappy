/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_gui_plv(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui == false || client->team == NULL)
        return;
    struct my_vector_s *args = string_split(buffer, " ");
    if (vector_length(args) != 2)
        return;
    int id = atoi(((struct my_string_s *)vector_get(args, 1))->str);
    struct client_s *target = vector_get(g->clients, id);
    if (target == NULL)
        return;
    dprintf(client->client_fd, "plv %d %d\n", id, target->level);
}
