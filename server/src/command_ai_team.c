/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void connect_to_team_after_hatch(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int index = string_to_int(buffer);
    struct egg_s *egg = vector_remove(g->eggs, index);
    struct my_tuple_s *slots = map_get(g->team_slots, egg->team, string_equals_str);
    int min = ((struct base_type_s *)tuple_get_first(slots))->_int;
    int max = ((struct base_type_s *)tuple_get_second(slots))->_int;
    if (min >= max) {
        dprintf(client->client_fd, "ko\n");
        return;
    }
    if (egg->is_forked == false) {
        int index = 0;
        for (int i = 0; i < vector_length(g->arg->names); i++) {
            if (string_equals_str(vector_get(g->arg->names, i), egg->team)) {
                index = i;
                break;
            }
        }
        g->arg->team_slots_server[index]--;
    }
    ((struct base_type_s *)tuple_get_first(slots))->_int++;
    min += 1;
    int remaining_slots = max - min;
    client->team = string_create();
    string_append(client->team, egg->team->str);
    client->is_gui = false;
    if (g->ai_spawn == false) {
        for (int i = 0; i < vector_length(g->map); i++) {
            for (int j = 0; j < vector_length(vector_get(g->map, i)); j++) {
                struct tile_s *tile = vector_get(vector_get(g->map, i), j);
                if (tile->food <= 0)
                    continue;
                struct my_string_s *msg = string_from_format("bct %d %d %d %d %d %d %d %d %d\n",
                i, j, tile->food, tile->linemate, tile->deraumere, tile->sibur,
                tile->mendiane, tile->phiras, tile->thystame);
                send_to_all_gui(g, msg->str);
                string_destroy(msg);
            }
        }
    }
    g->ai_spawn = true;
    client->food = 10;
    client->food_time = 0;

    bool is_forked_egg = egg->is_forked;
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
    if (is_forked_egg)
        send_to_all_gui(g, msg->str);
    string_destroy(msg);
    msg = string_from_format("pnw %d %d %d %d %d %s\n",
    client->client_nb, client->posx, client->posy, client->orientation,
    client->level, client->team->str);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
}

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
    int index = -1;
    for (int i = 0; i < vector_length(g->eggs); i++) {
        struct egg_s *egg = vector_get(g->eggs, i);
        if (string_equals_str(egg->team, name)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        dprintf(client->client_fd, "ko\n");
        return;
    }

    struct my_string_s *tmp = string_from_int(index);
    connect_to_team_after_hatch(g, client, tmp);
    string_destroy(tmp);
}
