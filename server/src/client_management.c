/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void accept_new_client(int select_result, struct global_struct_s *g)
{
    if (select_result > 0 && FD_ISSET(g->server->server_sock, &g->readset)) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(g->server->server_sock,
        (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd == -1)
            return;
        struct client_s *client = malloc(sizeof(struct client_s));
        client->client_fd = client_fd;
        client->is_closed = false;
        client->is_gui = false;
        client->buffer = string_create();
        client->team = NULL;
        client->posx = rand() % g->arg->width;
        client->posy = rand() % g->arg->height;
        client->orientation = rand() % 4 + 1;
        client->client_nb = g->client_id++;
        client->time = 0;
        client->exec = NULL;
        client->cmd = NULL;
        client->level = 1;
        client->food = 0;
        client->linemate = 0;
        client->deraumere = 0;
        client->sibur = 0;
        client->mendiane = 0;
        client->phiras = 0;
        client->thystame = 0;
        vector_push_back(g->clients, client);
        dprintf(client_fd, "WELCOME\n");
        printf("new client: x: %d, y: %d, orient: %d\n", client->posx, client->posy, client->orientation);
    }
}

void client_disconnection(struct client_s *client, struct global_struct_s *g)
{
    close(client->client_fd);
    client->is_closed = true;
    if (client->team != NULL && !client->is_gui) {
        ((struct base_type_s *)tuple_get_first(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
        ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
        // GUI Event
        struct my_string_s *msg = string_from_format("pdi %d\n",
        client->client_nb);
        send_to_all_gui(g, msg->str);
        string_destroy(msg);
    }
}

void manage_command_in_buffer(struct client_s *client, struct global_struct_s *g)
{
    // si ia en attente d'exec
    if (!client->is_gui && client->team != NULL && client->exec != NULL)
        return;

    // "str to line"
    struct my_vector_s *lines = string_split(client->buffer, "\n");
    for (int i = 0; i < vector_length(lines); i++) {
        struct my_string_s *line = vector_get(lines, i);
        if (i == vector_length(lines) - 1 && !string_endswith(client->buffer, "\n"))
            break;
        else
            string_append(line, "\n");
    }

    // garde que les 10 premiere commande (sujet)
    while (vector_length(lines) > 10)
        string_destroy(vector_pop_back(lines));

    // si c'est une ia simplement executer une commande
    // (ou plusieur si la commande n'a pas de délai)
    if (!client->is_gui && client->team != NULL) {
        while (client->exec == NULL && vector_length(lines)) {
            manage_command(g, client, (vector_get(lines, 0)));
            string_destroy(vector_remove(lines, 0));
        }
    } else // sinon faire toute les commande reçu
        while (vector_length(lines) > 0 && string_endswith(vector_get(lines, 0), "\n")) {
            manage_command(g, client, (vector_get(lines, 0)));
            string_destroy(vector_remove(lines, 0));
        }

    // vider le buffer
    string_clear(client->buffer);

    //remplir le buffer avec les commandes restantes
    for (int i = 0; i < vector_length(lines); i++)
        string_append(client->buffer, vector_get(lines, i));
    vector_destroy(lines);
}

void manage_specific_client(struct client_s *client, struct global_struct_s *g)
{
    if (FD_ISSET(client->client_fd, &g->readset)) {
        char buffer[BUFSIZ];
        memset(buffer, 0, BUFSIZ);
        read(client->client_fd, buffer, BUFSIZ);
        if (strlen(buffer) == 0) {
            client_disconnection(client, g);
            return;
        }
        string_append(client->buffer, buffer);
        if (strstr(client->buffer->str, "\n") != NULL)
            manage_command_in_buffer(client, g);
    }
}

bool ai_starve_eat(struct global_struct_s *g, struct client_s *client)
{
    if (client->food_time <= 0) {
        if (client->food > 0) {
            client->food--;
            client->food_time += FOOD_TIME;
        } else {
            dprintf(client->client_fd, "dead\n");
            close(client->client_fd);
            client->is_closed = true;
            ((struct base_type_s *)tuple_get_first(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
            ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
            // GUI Event
            struct my_string_s *msg = string_from_format("pdi %d\n",
            client->client_nb);
            send_to_all_gui(g, msg->str);
            string_destroy(msg);
            return true;
        }
    }
    return false;
}

void manage_clients(int select_result, struct global_struct_s *g)
{
    if (select_result == 0) { // timeout
        if (g->ressources_respawn <= 0)
            ressoure_respawn();
        for (int i = 0; i < vector_length(g->clients); i++) {
            struct client_s *client = vector_get(g->clients, i);
            if (client->is_closed || client->is_gui || client->team == NULL)
                continue;
            if (ai_starve_eat(g, client))
                continue;
            if (client->time <= 0 && client->exec != NULL) {
                client->exec(g, client, client->cmd);
                client->exec = NULL;
                if (client->cmd)
                    string_destroy(client->cmd);
                client->cmd = NULL;
            }
        }
        close_client();
        return;
    }
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed)
            continue;
        manage_specific_client(client, g);
    }
    close_client();
}
