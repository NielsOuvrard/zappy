/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void print_tile_content(struct my_string_s *response,
struct client_s *client, int x, int y)
{
    struct my_string_s *tmp_str = string_create();
    struct global_struct_s *g = get_global_struct();
    // check if there is a player on the tile
    for (int k = 0; k < vector_length(g->clients); k++) {
        struct client_s *tmp = vector_get(g->clients, k);
        if (tmp->posx == x && tmp->posy == y && tmp->is_gui == false)
            string_append(tmp_str, "player ");
    }
    // check if there is a resource on the tile
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->food; k++)
        string_append(tmp_str, "food ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->linemate; k++)
        string_append(tmp_str, "linemate ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->deraumere; k++)
        string_append(tmp_str, "deraumere ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->sibur; k++)
        string_append(tmp_str, "sibur ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->mendiane; k++)
        string_append(tmp_str, "mendiane ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->phiras; k++)
        string_append(tmp_str, "phiras ");
    for (int k = 0; k < ((struct tile_s *)vector_get(vector_get(g->map, y), x))->thystame; k++)
        string_append(tmp_str, "thystame ");
    // remove the last space
    if (string_length(tmp_str) > 0)
        string_remove_at(tmp_str, string_length(tmp_str) - 1);
    // append the tile content to the response
    if (string_length(tmp_str) > 0 && string_length(response) > 2)
        string_append(response, " ");
    string_append(response, tmp_str->str);
    // destroy the tmp string
    string_destroy(tmp_str);
}

void command_ai_look(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_string_s *response = string_create();
    string_append(response, "[ ");
    if (client->orientation == SOUTH)
        for (int i = 0; i < client->level + 1; i++) {
            for (int j = i; j > -i - 1; j--) {
                int x = client->posx + j;
                int y = client->posy + i;
                convert_coordinate(&x, &y);
                print_tile_content(response, client, x, y);
                if (!(i == client->level && j == -i))
                    string_append(response, ",");
            }
        }
    else if (client->orientation == NORTH)
        for (int i = 0; i < client->level + 1; i++) {
            for (int j = -i; j < i + 1; j++) {
                int x = client->posx + j;
                int y = client->posy - i;
                convert_coordinate(&x, &y);
                print_tile_content(response, client, x, y);
                if (!(i == client->level && j == i))
                    string_append(response, ",");
            }
        }
    else if (client->orientation == EAST)
        for (int i = 0; i < client->level + 1; i++) {
            for (int j = -i; j < i + 1; j++) {
                int x = client->posx + i;
                int y = client->posy + j;
                convert_coordinate(&x, &y);
                print_tile_content(response, client, x, y);
                if (!(i == client->level && j == i))
                    string_append(response, ",");
            }
        }
    else if (client->orientation == WEST)
        for (int i = 0; i < client->level + 1; i++) {
            for (int j = i; j > -i - 1; j--) {
                int x = client->posx - i;
                int y = client->posy + j;
                convert_coordinate(&x, &y);
                print_tile_content(response, client, x, y);
                if (!(i == client->level && j == -i))
                    string_append(response, ",");
            }
        }
    string_append(response, " ]\n");
    printf("look: %s", response->str);
    dprintf(client->client_fd, "%s", response->str);
    string_destroy(response);
}
