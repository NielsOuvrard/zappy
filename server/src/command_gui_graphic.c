/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_gui_graphic(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    client->is_gui = true;
    client->team = string_create();
    string_append(client->team, "GRAPHIC");
    send_to_client(client, "msz %d %d\n", g->arg->width, g->arg->height);
    send_to_client(client, "sgt %d\n", g->arg->freq);
    for (int i = 0; i < vector_length(g->map); i++) {
        for (int j = 0; j < vector_length(vector_get(g->map, i)); j++) {
            struct tile_s *tile = vector_get(vector_get(g->map, i), j);
            send_to_client(client, "bct %d %d %d %d %d %d %d %d %d\n",
            j, i, (g->ai_spawn ? tile->food : 0), tile->linemate,
            tile->deraumere, tile->sibur, tile->mendiane, tile->phiras,
            tile->thystame);
        }
    }
    for (int i = 0; i < vector_length(g->arg->names); i++)
        send_to_client(client, "tna %s\n",
        ((struct my_string_s *)vector_get(g->arg->names, i))->str);
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *target = vector_get(g->clients, i);
        if (target->is_gui == false && target->team != NULL)
            send_to_client(client, "pnw %d %d %d %d %d %s\n", target->client_nb,
            target->posx, target->posy, target->orientation, target->level,
            target->team->str);
    }
    for (int i = 0; i < vector_length(g->eggs); i++) {
        struct egg_s *egg = vector_get(g->eggs, i);
        if (egg->is_forked == false)
            continue;
        send_to_client(client, "enw %d %d %d %d\n", egg->id, 0,
        egg->posx, egg->posy);
    }
}
