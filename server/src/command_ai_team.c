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
    ((struct base_type_s *)tuple_get_first(slots))->_int++;
    min += 1;
    int remaining_slots = max - min;
    client->team = string_create();
    string_append(client->team, name->str);
    client->is_gui = false;
    g->ai_spawn = true;
    client->food = 10;
    client->food_time = 0;
    int index = 0;
    for (int i = 0; i < vector_length(g->eggs); i++) {
        struct egg_s *egg = vector_get(g->eggs, i);
        if (string_equals_str(egg->team, client->team)) {
            index = i;
            break;
        }
    }
    struct egg_s *egg = vector_remove(g->eggs, index);
    client->posx = egg->posx;
    client->posy = egg->posy;
    client->orientation = egg->orientation;
    int egg_id = egg->id;
    if (egg->team)
        string_destroy(egg->team);
    free(egg);
    dprintf(client->client_fd, "%d\n", remaining_slots);
    dprintf(client->client_fd, "%d %d\n", g->arg->width, g->arg->height);
    // GUI Event
    struct my_string_s *msg = string_from_format("ebo %d\n", egg_id);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
    msg = string_from_format("pnw %d %d %d %d %d %s\n",
    client->client_nb, client->posx, client->posy, client->orientation,
    client->level, client->team->str);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
}
