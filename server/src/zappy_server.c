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
    struct arg_s *arg = get_arg();
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

void initialize_map(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    global_struct->map = vector_create(sizeof(struct my_vector_s *));
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_create(sizeof(struct my_string_s *));
        for (int j = 0; j < arg->width; j++) {
            vector_push_back(line, string_from_string("X"));
        }
        vector_push_back(global_struct->map, line);
    }
    // print the map
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_get(global_struct->map, i);
        for (int j = 0; j < arg->width; j++) {
            struct my_string_s *str = vector_get(line, j);
            string_print(str);
        }
        printf("\n");
    }
}

void initialize_server(void)
{
    struct global_struct_s *g = get_global_struct();
    struct arg_s *arg = g->arg;
    struct server_s *server = malloc(sizeof(struct server_s));
    server->server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server->server_sock == -1) {
        printf("socket: %s", strerror(errno));
        exit(84);
    }
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(arg->port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(server->server_sock, SOL_SOCKET, (SO_REUSEADDR), (char*) &server->server_addr, sizeof(server->server_addr)) == -1)
        exit(84);
    if (bind(server->server_sock, (const struct sockaddr *) &server->server_addr, sizeof(server->server_addr)) == -1) {
        printf("bind: %s", strerror(errno));
        exit(84);
    }
    if (listen(server->server_sock, 1000) == -1) {
        printf("listen: %s", strerror(errno));
        exit(84);
    }
    g->server = server;
}

void free_all(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    vector_destroy(arg->names, string_destroy);
    for (int i = 0; i < vector_length(global_struct->map); i++)
        vector_destroy(vector_get(global_struct->map, i), string_destroy);
    vector_destroy(global_struct->map, NULL);
    free(global_struct->server);
}

int zappy_server(int ac, char **av)
{
    check_args(ac, av);
    initialize_map();
    initialize_server();
    free_all();
    return 0;
}
