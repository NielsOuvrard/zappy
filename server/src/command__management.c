/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void manage_command_no_team(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (string_equals(buffer, "GRAPHIC\n"))
        command_gui_graphic(g, client, buffer);
    else {
        for (int i = 0; i < vector_length(g->arg->names); i++) {
            struct my_string_s *name = vector_get(g->arg->names, i);
            if (string_startswith(buffer, name->str)) {
                command_ai_team(g, client, buffer, name);
                return;
            }
        }
        send_to_client(client, "ko\n"); // unknown command
    }
}

void manage_command_gui(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (string_equals(buffer, "msz\n"))
        command_gui_msz(g, client, buffer);
    else if (string_startswith(buffer, "bct "))
        command_gui_bct(g, client, buffer);
    else if (string_equals(buffer, "mct\n"))
        command_gui_mct(g, client, buffer);
    else if (string_equals(buffer, "tna\n"))
        command_gui_tna(g, client, buffer);
    else if (string_startswith(buffer, "ppo "))
        command_gui_ppo(g, client, buffer);
    else if (string_startswith(buffer, "plv "))
        command_gui_plv(g, client, buffer);
    else if (string_startswith(buffer, "pin "))
        command_gui_pin(g, client, buffer);
    else if (string_equals(buffer, "sgt\n"))
        command_gui_sgt(g, client, buffer);
    else if (string_startswith(buffer, "sst "))
        command_gui_sst(g, client, buffer);
    else
        send_to_client(client, "suc\n"); // unknown command
}

void manage_command_ai(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (string_equals(buffer, "Forward\n")) {
        client->time = 7;
        client->exec = command_ai_forward;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Right\n")) {
        client->time = 7;
        client->exec = command_ai_right;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Left\n")) {
        client->time = 7;
        client->exec = command_ai_left;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Look\n")) {
        client->time = 7;
        client->exec = command_ai_look;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Inventory\n")) {
        client->time = 1;
        client->exec = command_ai_inventory;
        client->cmd = string_copy(buffer);
    } else if (string_startswith(buffer, "Broadcast ")) {
        client->time = 7;
        client->exec = command_ai_broadcast;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Connect_nbr\n")) {
        command_ai_connect_nbr(g, client, buffer);
    } else if (string_equals(buffer, "Fork\n")) {
        client->time = 42;
        client->exec = command_ai_fork;
        client->cmd = string_copy(buffer);
        // GUI Event
        struct my_string_s *msg = string_from_format("pfk %d\n",
        client->client_nb);
        send_to_all_gui(g, msg->str);
        string_destroy(msg);
    } else if (string_equals(buffer, "Eject\n")) {
        client->time = 7;
        client->exec = command_ai_eject;
        client->cmd = string_copy(buffer);
    } else if (string_startswith(buffer, "Take ")) {
        client->time = 7;
        client->exec = command_ai_take;
        client->cmd = string_copy(buffer);
    } else if (string_startswith(buffer, "Set ")) {
        client->time = 7;
        client->exec = command_ai_set;
        client->cmd = string_copy(buffer);
    } else if (string_equals(buffer, "Incantation\n")) {
        command_ai_incantation_start(g, client, buffer);
        client->time = 300;
        client->exec = command_ai_incantation_end;
        client->cmd = string_copy(buffer);
    } else {
        send_to_client(client, "ko\n"); // unknown command
    }
}

void manage_command(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->team == NULL) {
        manage_command_no_team(g, client, buffer);
    } else if (client->is_gui) {
        manage_command_gui(g, client, buffer);
    } else {
        manage_command_ai(g, client, buffer);
    }
}
