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
    struct arg_s *arg = my_malloc(sizeof(struct arg_s));
    arg->port = 4242;
    arg->width = 10;
    arg->height = 10;
    arg->clientsNb = 1;
    arg->freq = 100;
    arg->names = vector_create(sizeof(struct my_string_s *));
    vector_set_destructor(arg->names, string_destroy);
    vector_push_back(arg->names, string_from_string("Team1"));
    vector_push_back(arg->names, string_from_string("Team2"));
    vector_push_back(arg->names, string_from_string("Team3"));
    vector_push_back(arg->names, string_from_string("Team4"));
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0)
            arg->port = atoi(av[i + 1]);
        if (strcmp(av[i], "-x") == 0)
            arg->width = atoi(av[i + 1]);
        if (strcmp(av[i], "-y") == 0)
            arg->height = atoi(av[i + 1]);
        if (strcmp(av[i], "-c") == 0)
            arg->clientsNb = atoi(av[i + 1]);
        if (strcmp(av[i], "-f") == 0)
            arg->freq = atoi(av[i + 1]);
        if (strcmp(av[i], "-n") == 0) {
            vector_destroy(arg->names);
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
            vector_set_destructor(arg->names, string_destroy);
        }
    }
    if (arg->width < MIN_WIDTH || arg->width > MAX_WIDTH) {
        dprintf(2, "Error: width must be between %d and %d\n", MIN_WIDTH, MAX_WIDTH);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    if (arg->height < MIN_HEIGHT || arg->height > MAX_HEIGHT) {
        dprintf(2, "Error: height must be between %d and %d\n", MIN_HEIGHT, MAX_HEIGHT);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    if (arg->clientsNb < MIN_CLIENTS_NB || arg->clientsNb > MAX_CLIENTS_NB) {
        dprintf(2, "Error: clientsNb must be between %d and %d\n", MIN_CLIENTS_NB, MAX_CLIENTS_NB);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    if (arg->freq < MIN_FREQ || arg->freq > MAX_FREQ) {
        dprintf(2, "Error: freq must be between %d and %d\n", MIN_FREQ, MAX_FREQ);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    if (vector_length(arg->names) < MIN_TEAMS_NB || vector_length(arg->names) > MAX_TEAMS_NB) {
        dprintf(2, "Error: teamsNb must be between %d and %d\n", MIN_TEAMS_NB, MAX_TEAMS_NB);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    if (arg->port < MIN_PORT || arg->port > MAX_PORT) {
        dprintf(2, "Error: port must be between %d and %d\n", MIN_PORT, MAX_PORT);
        vector_destroy(arg->names);
        free(arg);
        exit(84);
    }
    // check if 2 teams have the same name
    for (int i = 0; i < vector_length(arg->names); i++) {
        for (int j = i + 1; j < vector_length(arg->names); j++) {
            if (strcmp(((struct my_string_s *)vector_get(arg->names, i))->str,
                       ((struct my_string_s *)vector_get(arg->names, j))->str) == 0) {
                dprintf(2, "Error: teams must have different names\n");
                vector_destroy(arg->names);
                free(arg);
                exit(84);
            }
        }
    }
    arg->team_slots_server = my_malloc(sizeof(int) * vector_length(arg->names));
    struct global_struct_s *global_struct = get_global_struct();
    global_struct->arg = arg;
    global_struct->team_slots = map_create();
    map_set_destroy(global_struct->team_slots, string_destroy, tuple_destroy);
    printf("port: %d\n", arg->port);
    printf("width: %d\n", arg->width);
    printf("height: %d\n", arg->height);
    for (int i = 0; i < vector_length(arg->names); i++) {
        printf("names %d: %s\n", i, ((struct my_string_s *)vector_get(arg->names, i))->str);
        struct my_tuple_s *tuple = tuple_create();
        struct base_type_s *actual = my_malloc(sizeof(struct base_type_s));
        actual->_int = 0;
        struct base_type_s *max = my_malloc(sizeof(struct base_type_s));
        max->_int = arg->clientsNb;
        tuple_set(tuple, actual, max, free, free);
        map_insert(global_struct->team_slots,
        string_copy((struct my_string_s *)vector_get(arg->names, i)),
        tuple);
        global_struct->arg->team_slots_server[i] = global_struct->arg->clientsNb;
    }
    printf("clientsNb: %d\n", arg->clientsNb);
    printf("freq: %d\n", arg->freq);
}
