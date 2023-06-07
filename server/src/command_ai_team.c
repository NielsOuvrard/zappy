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
    int remaining_slots = string_to_int(map_get(g->team_slots, name, string_equals_str));
    if (remaining_slots == 0) {
        dprintf(client->client_fd, "ko\n");
        return;
    }
    remaining_slots--;
    map_set(g->team_slots, name, string_from_int(remaining_slots), string_equals_str, string_destroy);
    client->team = string_create();
    string_append(client->team, name->str);
    client->is_gui = false;
    dprintf(client->client_fd, "%d\n", remaining_slots);
    dprintf(client->client_fd, "%d %d\n", g->arg->width, g->arg->height);
}
