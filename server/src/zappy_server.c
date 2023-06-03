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
            arg->names = malloc(sizeof(char *) * (ac - i));
            int j = 0;
            for (j = 0; j < ac - i; j++) {
                if (strcmp(av[i + j + 1], "-p") == 0 ||
                    strcmp(av[i + j + 1], "-x") == 0 ||
                    strcmp(av[i + j + 1], "-y") == 0 ||
                    strcmp(av[i + j + 1], "-c") == 0 ||
                    strcmp(av[i + j + 1], "-f") == 0)
                    break;
                arg->names[j] = strdup(av[i + j + 1]);
            }
            for (int k = j; k < ac - i; k++)
                arg->names[k] = NULL;
        }
    }
    printf("port: %d\n", arg->port);
    printf("width: %d\n", arg->width);
    printf("height: %d\n", arg->height);
    for (int i = 0; arg->names[i] != NULL; i++)
        printf("names %d: %s\n", i, arg->names[i]);
    printf("clientsNb: %d\n", arg->clientsNb);
    printf("freq: %d\n", arg->freq);
}

int zappy_server(int ac, char **av)
{
    check_args(ac, av);
    struct arg_s *arg = get_arg();
    for (int i = 0; arg->names[i] != NULL; i++)
        free(arg->names[i]);
    free(arg->names);
    return 0;
}
