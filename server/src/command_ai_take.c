/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_take(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int x = client->posx;
    int y = client->posy;

    struct my_vector_s *arg = string_split(buffer, " ");

    if (vector_length(arg) != 2) {
        dprintf(client->client_fd, "ko\n");
        printf("Failed to take\n");
        vector_destroy(arg, string_destroy);
        return;
    }

    struct my_string_s *name = vector_get(arg, 1);

    if (string_equals(name, "food\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->food > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->food--;
        client->food++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "linemate\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->linemate > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->linemate--;
        client->linemate++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "deraumere\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->deraumere > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->deraumere--;
        client->deraumere++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "sibur\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->sibur > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->sibur--;
        client->sibur++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "mendiane\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->mendiane > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->mendiane--;
        client->mendiane++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "phiras\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->phiras > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->phiras--;
        client->phiras++;
        dprintf(client->client_fd, "ok\n");
    } else if (string_equals(name, "thystame\n") && ((struct tile_s *)vector_get(vector_get(g->map, y), x))->thystame > 0) {
        ((struct tile_s *)vector_get(vector_get(g->map, y), x))->thystame--;
        client->thystame++;
        dprintf(client->client_fd, "ok\n");
    } else {
        dprintf(client->client_fd, "ko\n");
        printf("Failed to take \"%s\"\n", name->str);
    }
    vector_destroy(arg, string_destroy);
}
