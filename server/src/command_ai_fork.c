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
    egg->id = g->egg_id++;
    egg->posx = client->posx;
    egg->posy = client->posy;
    egg->hatch_time = HATCH_TIME;
    egg->is_hatched = false;
    egg->is_forked = true;
    egg->orientation = client->orientation;
    egg->team = string_copy(client->team);
    vector_push_back(g->eggs, egg);
    ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int++;
    send_to_client(client, "ok\n");

    // GUI Event
    struct my_string_s *msg = string_from_format("enw %d %d %d %d\n",
    egg->id, client->client_nb, egg->posx, egg->posy);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
}
