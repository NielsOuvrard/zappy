/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_connect_nbr(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_tuple_s *slots = map_get(g->team_slots, client->team, string_equals_str);
    int min = ((struct base_type_s *)tuple_get_first(slots))->_int;
    int max = ((struct base_type_s *)tuple_get_second(slots))->_int;

    int remaning_slots = max - min;
    send_to_client(client, "%d\n", remaning_slots);
}
