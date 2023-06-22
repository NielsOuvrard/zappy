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
    struct my_string_s *inv = string_from_format("[food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d]\n",
    client->food, client->linemate, client->deraumere, client->sibur, client->mendiane, client->phiras, client->thystame);
    send_to_client(client, "%s", inv->str);
    string_destroy(inv);
}
