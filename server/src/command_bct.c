/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"


void command_bct(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->is_gui == false)
        return;
    struct my_vector_s *args = string_split(buffer, " ");
    int x = atoi(((struct my_string_s *)vector_get(args, 1))->str);
    int y = atoi(((struct my_string_s *)vector_get(args, 2))->str);
    convert_coordinate(&x, &y);
    struct tile_s *tile = vector_get(vector_get(g->map, y), x);
    dprintf(client->client_fd, "bct %d %d %d %d %d %d %d %d %d\n",
    x, y, tile->food, tile->linemate, tile->deraumere,
    tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
}
