/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_team(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer, struct my_string_s *name)
{
    struct my_tuple_s *slots = map_get(g->team_slots, name, string_equals_str);
    int min = ((struct base_type_s *)tuple_get_first(slots))->_int;
    int max = ((struct base_type_s *)tuple_get_second(slots))->_int;
    if (min == max) {
        dprintf(client->client_fd, "ko\n");
        return;
    }
    ((struct base_type_s *)tuple_get_first(slots))->_int--;
    int remaining_slots = max - min;
    client->team = string_create();
    string_append(client->team, name->str);
    client->is_gui = false;
    dprintf(client->client_fd, "%d\n", remaining_slots);
    dprintf(client->client_fd, "%d %d\n", g->arg->width, g->arg->height);
}
