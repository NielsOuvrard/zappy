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
    printf("port: %d\n", arg->port);
    printf("width: %d\n", arg->width);
    printf("height: %d\n", arg->height);
    for (int i = 0; i < vector_length(arg->names); i++)
        printf("names %d: %s\n", i, ((struct my_string_s *)vector_get(arg->names, i))->str);
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
        free(client);
    }
    vector_destroy(global_struct->clients, NULL);
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
        client->posx = 0;
        client->posy = 0;
        client->orientation = EAST;
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
        printf("new client\n");
    }
}

void manage_command(struct global_struct_s *g, struct client_s *client,
struct my_string_s *buffer)
{
    if (string_equals(buffer, "GRAPHIC\n"))
        command_graphic(g, client, buffer);
    else if (string_equals(buffer, "msz\n"))
        command_msz(g, client, buffer);
    else if (string_startswith(buffer, "bct "))
        command_bct(g, client, buffer);
    else if (string_equals(buffer, "mct\n"))
        command_mct(g, client, buffer);
    else if (string_equals(buffer, "tna\n"))
        command_tna(g, client, buffer);
    else if (string_startswith(buffer, "ppo "))
        command_ppo(g, client, buffer);
    else if (string_startswith(buffer, "plv "))
        command_plv(g, client, buffer);
    else if (string_startswith(buffer, "pin "))
        command_pin(g, client, buffer);
    else if (string_equals(buffer, "sgt\n"))
        command_sgt(g, client, buffer);
    else if (string_startswith(buffer, "sst "))
        command_sst(g, client, buffer);
    // else if (string_equals(buffer, "quit\n"))
    //     command_quit(g, client, buffer);
    else
        dprintf(client->client_fd, "suc\n"); // unknown command
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
            return;
        }
        if (strstr(buffer, "\n") != NULL) {
            string_append(client->buffer, buffer);
            manage_command(g, client, client->buffer);
            string_clear(client->buffer);
        } else {
            string_append(client->buffer, buffer);
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
}

int zappy_server(int ac, char **av)
{
    check_args(ac, av);
    initialize_map();
    initialize_server();
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
