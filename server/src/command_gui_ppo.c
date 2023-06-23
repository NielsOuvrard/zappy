/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_gui_ppo(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_vector_s *args = string_split(buffer, " ");
    if (vector_length(args) != 2)
        return;
    int id = atoi(((struct my_string_s *)vector_get(args, 1))->str);
    struct client_s *target = NULL;
    for (int i = 0; i < vector_length(g->clients); i++) {
        target = vector_get(g->clients, i);
        if (target->client_nb == id)
            break;
        target = NULL;
    }
    if (target == NULL || target->is_gui || target->team == NULL)
        return;
    send_to_client(client, "ppo %d %d %d %d\n", id, target->posx,
    target->posy, target->orientation);
}
