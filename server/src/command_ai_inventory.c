/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void command_ai_inventory(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_string_s *inventory = string_create();
    string_append(inventory, "[");
    string_append(inventory, "food ");
    string_append_int(inventory, client->food);
    string_append(inventory, ", linemate ");
    string_append_int(inventory, client->linemate);
    string_append(inventory, ", deraumere ");
    string_append_int(inventory, client->deraumere);
    string_append(inventory, ", sibur ");
    string_append_int(inventory, client->sibur);
    string_append(inventory, ", mendiane ");
    string_append_int(inventory, client->mendiane);
    string_append(inventory, ", phiras ");
    string_append_int(inventory, client->phiras);
    string_append(inventory, ", thystame ");
    string_append_int(inventory, client->thystame);
    string_append(inventory, "]\n");
    dprintf(client->client_fd, "%s", inventory->str);
    string_destroy(inventory);
}
