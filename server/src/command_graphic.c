/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_graphic(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    client->is_gui = true;
    dprintf(client->client_fd, "msz %d %d\n", g->arg->width, g->arg->height);
    dprintf(client->client_fd, "sgt %d\n", g->arg->freq);
    for (int i = 0; i < vector_length(g->map); i++) {
        for (int j = 0; j < vector_length(vector_get(g->map, i)); j++) {
            struct tile_s *tile = vector_get(vector_get(g->map, i), j);
            dprintf(client->client_fd, "bct %d %d %d %d %d %d %d %d %d\n",
            i, j, tile->food, tile->linemate, tile->deraumere,
            tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
        }
    }
    for (int i = 0; i < vector_length(g->arg->names); i++)
        dprintf(client->client_fd, "tna %s\n",
        ((struct my_string_s *)vector_get(g->arg->names, i))->str);
}
