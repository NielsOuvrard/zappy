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
    struct my_string_s *str = map_get(g->team_slots, client->team, string_equals_str);

    if (str == NULL) {
        dprintf(client->client_fd, "ko\n");
        return;
    }
    int remaning_slots = string_to_int(str);
    dprintf(client->client_fd, "%d\n", remaning_slots);
    string_destroy(str);
}
