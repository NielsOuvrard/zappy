/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void print_help()
{
    printf("Usage: ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit ");
    printf("for execution of actions\n");
}

void check_args(int ac, char **av)
{
    if (ac == 2 && (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)) {
        print_help();
        exit(0);
    }
    if (ac < 13) {
        print_help();
        exit(84);
    }
    struct arg_s *arg = malloc(sizeof(struct arg_s));
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0 && atoi(av[i + 1]) > 0)
            arg->port = atoi(av[i + 1]);
        if (strcmp(av[i], "-x") == 0 && atoi(av[i + 1]) > 0)
            arg->width = atoi(av[i + 1]);
        if (strcmp(av[i], "-y") == 0 && atoi(av[i + 1]) > 0)
            arg->height = atoi(av[i + 1]);
        if (strcmp(av[i], "-c") == 0 && atoi(av[i + 1]) > 0)
            arg->clientsNb = atoi(av[i + 1]);
        if (strcmp(av[i], "-f") == 0 && atoi(av[i + 1]) > 0)
            arg->freq = atoi(av[i + 1]);
        if (strcmp(av[i], "-n") == 0) {
            arg->names = vector_create(sizeof(struct my_string_s *));
            int j = 0;
            for (j = 0; j < ac - i; j++) {
                if (strcmp(av[i + j + 1], "-p") == 0 ||
                    strcmp(av[i + j + 1], "-x") == 0 ||
                    strcmp(av[i + j + 1], "-y") == 0 ||
                    strcmp(av[i + j + 1], "-c") == 0 ||
                    strcmp(av[i + j + 1], "-f") == 0)
                    break;
                vector_push_back(arg->names, string_from_string(av[i + j + 1]));
            }
        }
    }
    struct global_struct_s *global_struct = get_global_struct();
    global_struct->arg = arg;
    global_struct->team_slots = map_create();
    printf("port: %d\n", arg->port);
    printf("width: %d\n", arg->width);
    printf("height: %d\n", arg->height);
    for (int i = 0; i < vector_length(arg->names); i++) {
        printf("names %d: %s\n", i, ((struct my_string_s *)vector_get(arg->names, i))->str);
        struct my_tuple_s *tuple = tuple_create();
        struct base_type_s *actual = malloc(sizeof(struct base_type_s));
        actual->_int = 0;
        struct base_type_s *max = malloc(sizeof(struct base_type_s));
        max->_int = arg->clientsNb;
        tuple_set(tuple, actual, max, free, free);
        map_insert(global_struct->team_slots,
        string_copy((struct my_string_s *)vector_get(arg->names, i)),
        tuple);
    }
    printf("clientsNb: %d\n", arg->clientsNb);
    printf("freq: %d\n", arg->freq);
}

void free_all(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    vector_destroy(arg->names, string_destroy);
    for (int i = 0; i < vector_length(global_struct->map); i++)
        vector_destroy(vector_get(global_struct->map, i), free);
    vector_destroy(global_struct->map, NULL);
    for (int i = 0; i < vector_length(global_struct->clients); i++) {
        struct client_s *client = vector_get(global_struct->clients, i);
        string_destroy(client->buffer);
        if (client->team)
            string_destroy(client->team);
        free(client);
    }
    vector_destroy(global_struct->clients, NULL);
    map_destroy(global_struct->team_slots, string_destroy, tuple_destroy);
    free(global_struct->arg);
    free(global_struct->server);
}

void set_fd_set(struct global_struct_s *g)
{
    g->maxfd = g->server->server_sock + 1;
    FD_ZERO(&g->readset);
    FD_ZERO(&g->writeset);
    FD_SET(g->server->server_sock, &g->readset);
    FD_SET(g->server->server_sock, &g->writeset);
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed)
            continue;
        FD_SET(client->client_fd, &g->readset);
        if (client->client_fd + 1 > g->maxfd)
            g->maxfd = client->client_fd + 1;
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
        client->client_fd = client_fd;
        client->is_closed = false;
        client->is_gui = false;
        client->buffer = string_create();
        client->team = NULL;
        client->posx = rand() % g->arg->width;
        client->posy = rand() % g->arg->height;
        client->orientation = rand() % 4 + 1;
        client->client_nb = g->client_id++;
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

void manage_command(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (client->team == NULL) { // connection to a team
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
            dprintf(client->client_fd, "ko\n"); // unknown command
        }
    }
    else if (client->is_gui) { // commands for gui
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
            dprintf(client->client_fd, "suc\n"); // unknown command
    } else { // commands for ai
        if (string_equals(buffer, "Forward\n"))
            command_ai_forward(g, client, buffer);
        else if (string_equals(buffer, "Right\n"))
            command_ai_right(g, client, buffer);
        else if (string_equals(buffer, "Left\n"))
            command_ai_left(g, client, buffer);
        else if (string_equals(buffer, "Look\n"))
            command_ai_look(g, client, buffer);
        else if (string_equals(buffer, "Inventory\n"))
            command_ai_inventory(g, client, buffer);
        else if (string_startswith(buffer, "Broadcast "))
            command_ai_broadcast(g, client, buffer);
        else if (string_equals(buffer, "Connect_nbr\n"))
            command_ai_connect_nbr(g, client, buffer);
        // else if (string_equals(buffer, "Fork\n"))
        //     command_ai_fork(g, client, buffer);
        else if (string_equals(buffer, "Eject\n"))
            command_ai_eject(g, client, buffer);
        else if (string_startswith(buffer, "Take "))
            command_ai_take(g, client, buffer);
        else if (string_startswith(buffer, "Set "))
            command_ai_set(g, client, buffer);
        // else if (string_equals(buffer, "Incantation\n"))
        //     command_ai_incantation(g, client, buffer);
        else {
            dprintf(client->client_fd, "ko\n"); // unknown command
        }
    }
}

void manage_specific_client(struct client_s *client, struct global_struct_s *g)
{
    if (FD_ISSET(client->client_fd, &g->readset)) {
        char buffer[BUFSIZ];
        memset(buffer, 0, BUFSIZ);
        read(client->client_fd, buffer, BUFSIZ);
        if (strlen(buffer) == 0) {
            close(client->client_fd);
            client->is_closed = true;
            if (client->team != NULL && !client->is_gui) {
                struct global_struct_s *g = get_global_struct();
                ((struct base_type_s *)tuple_get_first(map_get(g->team_slots, client->team, string_equals_str)))->_int--;
            }
            return;
        }
        if (strstr(buffer, "\n") != NULL) {
            string_append(client->buffer, buffer);
            struct my_vector_s *lines = string_split(client->buffer, "\n");
            for (int i = 0; i < vector_length(lines); i++) {
                struct my_string_s *line = vector_get(lines, i);
                if (i == vector_length(lines) - 1 && !string_endswith(client->buffer, "\n"))
                    break;
                else
                    string_append(line, "\n");
            }
            while (vector_length(lines) > 10)
                string_destroy(vector_pop_back(lines));
            while (vector_length(lines) > 0 && string_endswith(vector_get(lines, 0), "\n")) {
                manage_command(g, client, (vector_get(lines, 0)));
                string_destroy(vector_remove(lines, 0));
            }
            string_clear(client->buffer);
            if (vector_length(lines) > 0)
                string_append(client->buffer, vector_get(lines, 0));
            vector_destroy(lines, string_destroy);
        } else {
            string_append(client->buffer, buffer);
        }
    }
}

void close_client(void)
{
    struct global_struct_s *g = get_global_struct();
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed) {
            struct client_s *tmp = vector_remove(g->clients, i);
            i--;
            string_destroy(tmp->buffer);
            if (tmp->team)
                string_destroy(tmp->team);
            free(tmp);
        }
    }
}

void manage_clients(struct global_struct_s *g)
{
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed)
            continue;
        manage_specific_client(client, g);
    }
    close_client();
}

void sigint_handler(int sig)
{
    (void) sig;
    free_all();
    exit(0);
}

int zappy_server(int ac, char **av)
{
    check_args(ac, av);
    initialize_map();
    initialize_server();
    signal(SIGINT, sigint_handler);
    struct global_struct_s *g = get_global_struct();
    g->clients = vector_create(sizeof(struct client_s *));
    while (true) {
        set_fd_set(g);
        int select_result = select(g->maxfd, &g->readset, NULL, NULL, NULL);
        accept_new_client(select_result, g);
        manage_clients(g);
    }
    free_all();
    return 0;
}
