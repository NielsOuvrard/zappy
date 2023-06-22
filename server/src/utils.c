/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void convert_coordinate(int *x, int *y)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    *x = *x % arg->width;
    *y = *y % arg->height;
    while (*x < 0)
        *x = arg->width + *x;
    while (*y < 0)
        *y = arg->height + *y;
}

void send_to_all_gui(struct global_struct_s *global_struct, char *msg)
{
    for (int i = 0; i < vector_length(global_struct->clients); i++) {
        struct client_s *client = vector_get(global_struct->clients, i);
        if (client->is_gui) {
            int return_value = dprintf(client->network_client->client_fd, "%s", msg);
            if (return_value < 0)
                client_disconnection(client, get_global_struct());
        }
    }
}

void send_to_client(struct client_s *client, char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int return_value = vdprintf(client->network_client->client_fd, format, ap);
    if (return_value < 0)
        client_disconnection(client, get_global_struct());
    va_end(ap);
}
