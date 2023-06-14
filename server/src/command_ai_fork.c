/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_fork(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct egg_s *egg = malloc(sizeof(struct egg_s));
    egg->posx = client->posx;
    egg->posy = client->posy;
    egg->orientation = client->orientation;
    egg->team = string_copy(client->team);
    vector_push_back(g->eggs, egg);
    ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int++;
    dprintf(client->client_fd, "ok\n");
}
