/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void do_nothing(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    return;
}

void command_ai_incantation_start(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_vector_s *need = g->incant_need;
    struct incant_s *incant = vector_get(need, client->level - 1);
    int nb_players = 1;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->posx == client->posx && tmp->posy == client->posy && tmp->level == client->level && client != tmp && !tmp->is_gui)
            nb_players++;
    }
    if (nb_players < incant->nb_players) {
        dprintf(client->client_fd, "ko\n");
        return;
    }
    struct tile_s *tile = vector_get(vector_get(g->map, client->posy), client->posx);
    if (tile->linemate < incant->linemate ||
        tile->deraumere < incant->deraumere ||
        tile->sibur < incant->sibur ||
        tile->mendiane < incant->mendiane ||
        tile->phiras < incant->phiras ||
        tile->thystame < incant->thystame) {
        dprintf(client->client_fd, "ko\n");
        return;
    }

    struct my_string_s *msg = string_from_format("pic %d %d %d %d",
    client->posx, client->posy, client->level, client->client_nb);
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->posx == client->posx && tmp->posy == client->posy && tmp->level == client->level && client != tmp && !tmp->is_gui) {
            string_append(msg, " ");
            string_append_int(msg, tmp->client_nb);
            dprintf(tmp->client_fd, "Elevation underway\n");
            tmp->time = 300;
            tmp->exec = do_nothing;
            tmp->cmd = string_copy(buffer);
        }
    }
    // GUI Event
    string_append(msg, "\n");
    send_to_all_gui(g, msg->str);
    string_destroy(msg);
    dprintf(client->client_fd, "Elevation underway\n");
}

void command_ai_incantation_end(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    struct my_vector_s *need = g->incant_need;
    struct incant_s *incant = vector_get(need, client->level - 1);
    int nb_players = 1;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->posx == client->posx && tmp->posy == client->posy && tmp->level == client->level && client != tmp && !tmp->is_gui)
            nb_players++;
    }
    if (nb_players < incant->nb_players) {
        dprintf(client->client_fd, "ko\n");
        // GUI Event
        struct my_string_s *msg = string_from_format("pie %d %d 0\n",
        client->posx, client->posy);
        send_to_all_gui(g, msg->str);
        string_destroy(msg);
        return;
    }
    struct tile_s *tile = vector_get(vector_get(g->map, client->posy), client->posx);
    if (tile->linemate < incant->linemate ||
        tile->deraumere < incant->deraumere ||
        tile->sibur < incant->sibur ||
        tile->mendiane < incant->mendiane ||
        tile->phiras < incant->phiras ||
        tile->thystame < incant->thystame) {
        dprintf(client->client_fd, "ko\n");
        // GUI Event
        struct my_string_s *msg = string_from_format("pie %d %d 0\n",
        client->posx, client->posy);
        send_to_all_gui(g, msg->str);
        string_destroy(msg);
        return;
    }
    tile->linemate -= incant->linemate;
    tile->deraumere -= incant->deraumere;
    tile->sibur -= incant->sibur;
    tile->mendiane -= incant->mendiane;
    tile->phiras -= incant->phiras;
    tile->thystame -= incant->thystame;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->posx == client->posx && tmp->posy == client->posy && tmp->level == client->level && client != tmp && !tmp->is_gui) {
            tmp->level++;
            dprintf(tmp->client_fd, "Current level: %d\n", client->level);
        }
    }
    client->level++;
    dprintf(client->client_fd, "Current level: %d\n", client->level);

    // GUI Event
    struct my_string_s *msg = string_from_format("pie %d %d 1\n",
    client->posx, client->posy);
    send_to_all_gui(g, msg->str);
    string_destroy(msg);

    // check if a team win
    bool a_team_win = false;
    struct my_map_s *team_lvl8 = map_create();
    struct my_string_s *team = NULL;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *tmp = vector_get(g->clients, i);
        if (tmp->is_gui || tmp->level != 8)
            continue;
        if (map_get(team_lvl8, tmp->team, string_equals_str) == NULL) {
            struct base_type_s *base = malloc(sizeof(struct base_type_s));
            base->_int = 1;
            map_insert(team_lvl8, string_copy(tmp->team), base);
        } else {
            ((struct base_type_s *)map_get(team_lvl8, tmp->team, string_equals_str))->_int++;
        }
    }
    for (int i = 0; i < vector_length(g->arg->names); i++) {
        struct my_string_s *tmp = vector_get(g->arg->names, i);
        if (map_get(team_lvl8, tmp, string_equals_str) != NULL && ((struct base_type_s *)map_get(team_lvl8, tmp, string_equals_str))->_int >= 6) {
            a_team_win = true;
            team = tmp;
        }
    }

    // send message to all clients about the end of the incantation
    if (a_team_win) {
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *tmp = vector_get(g->clients, i);
            if (tmp->is_gui)
                dprintf(tmp->client_fd, "seg %s\n", client->team->str);
            else if (string_equals_str(tmp->team, team))
                dprintf(tmp->client_fd, "You Win!\n");
            else
                dprintf(tmp->client_fd, "dead\n");
        }
    }

    // destroy allocated memory
    map_set_destroy(team_lvl8, string_destroy, free);
    map_destroy(team_lvl8);
}
