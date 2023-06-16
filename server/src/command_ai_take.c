/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void gui_event_take(struct global_struct_s *g, struct client_s *client,
struct tile_s *tile, int type)
{
    struct my_string_s *msg = string_from_format("pgt %d %d\n",
    client->client_nb, type);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);

    struct my_string_s *inv = string_from_format("pin %d %d %d %d %d %d %d %d %d %d\n",
    client->client_nb, client->posx, client->posy, client->food, client->linemate,
    client->deraumere, client->sibur, client->mendiane, client->phiras, client->thystame);
    send_to_all_gui(g, inv->str);
    string_destroy(inv);

    struct my_string_s *current_tile = string_from_format("bct %d %d %d %d %d %d %d %d %d\n",
    client->posx, client->posy, tile->food, tile->linemate, tile->deraumere,
    tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
    send_to_all_gui(g, current_tile->str);
    string_destroy(current_tile);
}

void command_ai_take(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int x = client->posx;
    int y = client->posy;

    struct my_vector_s *arg = string_split(buffer, " ");

    if (vector_length(arg) != 2) {
        dprintf(client->client_fd, "ko\n");
        vector_destroy(arg);
        return;
    }

    struct my_string_s *name = vector_get(arg, 1);
    struct tile_s *tile = vector_get(vector_get(g->map, y), x);

    if (string_equals(name, "food\n") && tile->food > 0) {
        tile->food--;
        client->food++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 0);
    } else if (string_equals(name, "linemate\n") && tile->linemate > 0) {
        tile->linemate--;
        client->linemate++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 1);
    } else if (string_equals(name, "deraumere\n") && tile->deraumere > 0) {
        tile->deraumere--;
        client->deraumere++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 2);
    } else if (string_equals(name, "sibur\n") && tile->sibur > 0) {
        tile->sibur--;
        client->sibur++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 3);
    } else if (string_equals(name, "mendiane\n") && tile->mendiane > 0) {
        tile->mendiane--;
        client->mendiane++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 4);
    } else if (string_equals(name, "phiras\n") && tile->phiras > 0) {
        tile->phiras--;
        client->phiras++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 5);
    } else if (string_equals(name, "thystame\n") && tile->thystame > 0) {
        tile->thystame--;
        client->thystame++;
        dprintf(client->client_fd, "ok\n");
        // GUI Event
        gui_event_take(g, client, tile, 6);
    } else
        dprintf(client->client_fd, "ko\n");
    vector_destroy(arg);
}
