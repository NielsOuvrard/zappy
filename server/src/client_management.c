/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void generate_missing_eggs(struct global_struct_s *g)
{
    for (int i = 0; i < vector_length(g->arg->names); i++) {
        struct my_string_s *name = vector_get(g->arg->names, i);
        // if slot nb is less than the number of client allowed by team
        // recreate an egg for this team
        while (g->arg->team_slots_server[i] < g->arg->clientsNb) {
            g->arg->team_slots_server[i]++;
            ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, name, string_equals_str)))->_int++;
            struct egg_s *egg = malloc(sizeof(struct egg_s));
            egg->id = g->egg_id++;
            egg->posx = rand() % g->arg->width;
            egg->posy = rand() % g->arg->height;
            egg->hatch_time = 0;
            egg->is_hatched = true;
            egg->is_forked = false;
            egg->orientation = rand() % 4 + 1;
            egg->team = string_copy(name);
            vector_push_back(g->eggs, egg);
        }
    }
}

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
        client->network_client = malloc(sizeof(struct network_client_s));
        client->network_client->client_fd = client_fd;
        client->network_client->buffer = string_create();
        client->is_closed = false;
        client->is_gui = false;
        client->team = NULL;
        client->posx = rand() % g->arg->width;
        client->posy = rand() % g->arg->height;
        client->orientation = rand() % 4 + 1;
        client->client_nb = g->client_id++;
        client->time = 0;
        client->exec = NULL;
        client->cmd = NULL;
        client->is_incanting = -1;
        client->level = 1;
        client->food = 0;
        client->linemate = 0;
        client->deraumere = 0;
        client->sibur = 0;
        client->mendiane = 0;
        client->phiras = 0;
        client->thystame = 0;
        vector_push_back(g->clients, client);
        send_to_client(client, "WELCOME\n");
        printf("new client: x: %d, y: %d, orient: %d\n", client->posx, client->posy, client->orientation);
    }
}

void client_disconnection(struct client_s *client, struct global_struct_s *g)
{
    close(client->network_client->client_fd);
    client->is_closed = true;
    if (client->team != NULL && !client->is_gui) {
        ((struct base_type_s *)tuple_get_first(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
        ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
        generate_missing_eggs(g);
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
    struct my_vector_s *lines = string_split(client->network_client->buffer, "\n");
    for (int i = 0; i < vector_length(lines); i++) {
        struct my_string_s *line = vector_get(lines, i);
        if (i == vector_length(lines) - 1 && !string_endswith(client->network_client->buffer, "\n"))
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
    string_clear(client->network_client->buffer);

    //remplir le buffer avec les commandes restantes
    for (int i = 0; i < vector_length(lines); i++)
        string_append(client->network_client->buffer, vector_get(lines, i));
    vector_destroy(lines);
}

void manage_specific_client(struct client_s *client, struct global_struct_s *g)
{
    if (FD_ISSET(client->network_client->client_fd, &g->readset)) {
        char buffer[BUFSIZ];
        memset(buffer, 0, BUFSIZ);
        int return_value = read(client->network_client->client_fd, buffer, BUFSIZ);
        if (return_value <= 0) {
            client_disconnection(client, g);
            return;
        }
        if (strlen(buffer) == 0) {
            client_disconnection(client, g);
            return;
        }
        string_append(client->network_client->buffer, buffer);
        if (strstr(client->network_client->buffer->str, "\n") != NULL)
            manage_command_in_buffer(client, g);
        else if (strlen(client->network_client->buffer->str) > 10000)
            client_disconnection(client, g);
    }
}

bool ai_starve_eat(struct global_struct_s *g, struct client_s *client)
{
    if (client->food_time <= 0) {
        if (client->food > 0) {
            client->food--;
            client->food_time += FOOD_TIME;
            // GUI Event
            struct my_string_s *msg = string_from_format("pin %d %d %d %d %d %d %d %d %d %d\n",
            client->client_nb, client->posx, client->posy, client->food,
            client->linemate, client->deraumere, client->sibur,
            client->mendiane, client->phiras, client->thystame);
            send_to_all_gui(g, msg->str);
            string_destroy(msg);
        } else {
            send_to_client(client, "dead\n");
            close(client->network_client->client_fd);
            client->is_closed = true;
            ((struct base_type_s *)tuple_get_first(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
            ((struct base_type_s *)tuple_get_second(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
            generate_missing_eggs(g);
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
            if (client->is_closed || client->is_gui)
                continue;
            if (client->team != NULL)
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
