/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void gui_event_eject(struct global_struct_s *g, struct client_s *client)
{
    struct my_string_s *msg = string_from_format("ppo %d %d %d %d\n", client->client_nb,
    client->posx, client->posy, client->orientation);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
}

void command_ai_eject(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    int x = client->posx;
    int y = client->posy;

    struct my_string_s *msg = string_from_format("pex %d\n", client->client_nb);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);

    bool success = false;
    if (client->orientation == NORTH) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posy = (tmp->posy - 1 + g->arg->height) % g->arg->height;
                dprintf(tmp->client_fd, "eject: %d\n", SOUTH);
                success = true;
                gui_event_eject(g, tmp);
            }
        }
    } else if (client->orientation == SOUTH) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posy = (tmp->posy + 1) % g->arg->height;
                dprintf(tmp->client_fd, "eject: %d\n", NORTH);
                success = true;
                gui_event_eject(g, tmp);
            }
        }
    } else if (client->orientation == EAST) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posx = (tmp->posx + 1) % g->arg->width;
                dprintf(tmp->client_fd, "eject: %d\n", WEST);
                success = true;
                gui_event_eject(g, tmp);
            }
        }
    } else if (client->orientation == WEST) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->posx == x && tmp->posy == y) {
                tmp->posx = (tmp->posx - 1 + g->arg->width) % g->arg->width;
                dprintf(tmp->client_fd, "eject: %d\n", EAST);
                success = true;
                gui_event_eject(g, tmp);
            }
        }
    }
    for (int i = 0; i < vector_length(g->eggs); i++) {
        struct egg_s *tmp = vector_get(g->eggs, i);
        if (tmp->posx == x && tmp->posy == y) {
            // destroy egg
            struct egg_s *egg = vector_remove(g->eggs, i);
            // GUI Event
            struct my_string_s *msg = string_from_format("edi %d\n", egg->id);
            send_to_all_gui(g, msg->str);
            string_destroy(msg);
            if (egg->team) {
                ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, egg->team, string_equals_str)))->_int--;
                string_destroy(egg->team);
            }
            free(egg);
            success = true;
            i--;
        }
    }
    if (success)
        dprintf(client->client_fd, "ok\n");
    else
        dprintf(client->client_fd, "ko\n");
}
