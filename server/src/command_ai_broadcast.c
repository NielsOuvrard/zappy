/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void calc_shortest_path(struct global_struct_s *g, struct client_s *client,
struct client_s *tmp, int *x, int *y)
{
    int x1 = client->posx - tmp->posx;
    int x2 = (client->posx - g->arg->width) - tmp->posx;
    int y1 = client->posy - tmp->posy;
    int y2 = (client->posy - g->arg->height) - tmp->posy;

    *x = (abs(x1) > abs(x2) ? x2 : x1);
    *y = (abs(y1) > abs(y2) ? y2 : y1);
}

int calc_orientation(struct global_struct_s *g, struct client_s *client,
struct client_s *tmp)
{
    // if the two clients are on the same tile, return 0
    if (client->posx == tmp->posx && client->posy == tmp->posy)
        return (0);

    int orientation = 0;

    int x = 0;
    int y = 0;
    calc_shortest_path(g, client, tmp, &x, &y);

    // calculate angle of rotation between the two clients (in degrees)
    // considering the origin is tmp and the target is client
    // 0° is east, 90° is north, 180° is west, 270° is south, etc...
    double angle = atan2(-y, x) * 180 / M_PI;

    // convert angle to positive value
    if (angle < 0)
        angle += 360;

    // convert angle to orientation
    // N = 1, NW = 2, W = 3, SW = 4, S = 5, SE = 6, E = 7, NE = 8
    if (angle >= 337.5 || angle < 22.5)
        orientation = 7; // E
    else if (angle >= 22.5 && angle < 67.5)
        orientation = 8; // NE
    else if (angle >= 67.5 && angle < 112.5)
        orientation = 1; // N
    else if (angle >= 112.5 && angle < 157.5)
        orientation = 2; // NW
    else if (angle >= 157.5 && angle < 202.5)
        orientation = 3; // W
    else if (angle >= 202.5 && angle < 247.5)
        orientation = 4; // SW
    else if (angle >= 247.5 && angle < 292.5)
        orientation = 5; // S
    else if (angle >= 292.5 && angle < 337.5)
        orientation = 6; // SE

    // rotate orientation to match tmp's orientation
    if (tmp->orientation == NORTH)
        orientation = orientation;
    else if (tmp->orientation == EAST)
        orientation = (orientation + 2) % 8;
    else if (tmp->orientation == SOUTH)
        orientation = (orientation + 4) % 8;
    else if (tmp->orientation == WEST)
        orientation = (orientation + 6) % 8;

    if (orientation == 0)
        orientation = 8;

    return (orientation);
}

void command_ai_broadcast(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    for (int i = 0; i < strlen("Broadcast "); i++)
        string_remove_at(buffer, 0);
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->is_gui == false && tmp->client_fd != client->client_fd && tmp->is_closed == false) {
            int orientation = calc_orientation(g, client, tmp);
            send_to_client(tmp, "message %d, %s", orientation,
            buffer->str);
        }
        // GUI Event
        if (tmp->is_gui == true && tmp->client_fd != client->client_fd && tmp->is_closed == false) {
            send_to_client(tmp, "pbc %d %s", client->client_nb,
            buffer->str);
        }
    }
    send_to_client(client, "ok\n");
}
