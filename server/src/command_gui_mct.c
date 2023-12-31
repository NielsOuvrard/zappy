/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_gui_mct(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    for (int i = 0; i < vector_length(g->map); i++) {
        for (int j = 0; j < vector_length(vector_get(g->map, i)); j++) {
            struct tile_s *tile = vector_get(vector_get(g->map, i), j);
            send_to_client(client, "bct %d %d %d %d %d %d %d %d %d\n",
            j, i, (g->ai_spawn ? tile->food : 0), tile->linemate,
            tile->deraumere, tile->sibur, tile->mendiane, tile->phiras,
            tile->thystame);
        }
    }
}
