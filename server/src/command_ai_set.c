/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_set(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int x = client->posx;
    int y = client->posy;

    struct my_vector_s *arg = string_split(buffer, " ");

    if (vector_length(arg) != 2) {
        dprintf(client->client_fd, "ko\n");
        vector_destroy(arg, string_destroy);
        return;
    }

    struct my_string_s *name = vector_get(arg, 1);

    if (string_equals(name, "food\n") && client->food > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->food++;
        client->food--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "linemate\n") && client->linemate > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->linemate++;
        client->linemate--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "deraumere\n") && client->deraumere > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->deraumere++;
        client->deraumere--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "sibur\n") && client->sibur > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->sibur++;
        client->sibur--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "mendiane\n") && client->mendiane > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->mendiane++;
        client->mendiane--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "phiras\n") && client->phiras > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->phiras++;
        client->phiras--;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "thystame\n") && client->thystame > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->thystame++;
        client->thystame--;
        dprintf(client->client_fd, "ok\n");
    } else
        dprintf(client->client_fd, "ko\n");
    vector_destroy(arg, string_destroy);
}
