/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void set_fd_set(struct global_struct_s *g)
{
    g->maxfd = g->server->server_sock + 1;
    FD_ZERO(&g->readset);
    FD_ZERO(&g->writeset);
    FD_SET(g->server->server_sock, &g->readset);
    FD_SET(g->server->server_sock, &g->writeset);
    g->lowest_time = 0;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed)
            continue;
        FD_SET(client->client_fd, &g->readset);
        if (client->client_fd + 1 > g->maxfd)
            g->maxfd = client->client_fd + 1;
        if (client->is_gui || client->team == NULL)
            continue;
        if (client->time > 0 && (client->time < g->lowest_time || g->lowest_time == 0))
            g->lowest_time = client->time;
        if (client->food_time > 0 && (client->food_time < g->lowest_time || g->lowest_time == 0))
            g->lowest_time = client->food_time;
    }
    if (g->ressources_respawn > 0 && (g->ressources_respawn < g->lowest_time || g->lowest_time == 0))
        g->lowest_time = g->ressources_respawn;
    if (g->lowest_time > 0) {
        g->timeout.tv_sec = g->lowest_time / g->arg->freq;
        g->timeout.tv_usec = (g->lowest_time % g->arg->freq) * 1000000 / g->arg->freq;
    } else {
        g->timeout.tv_sec = 0;
        g->timeout.tv_usec = 0;
    }
}

void remove_past_time(struct global_struct_s *g)
{
    int tmp = g->timeout.tv_sec * g->arg->freq;
    tmp += g->timeout.tv_usec * g->arg->freq / 1000000;
    for (int i = 0; i < vector_length(g->clients); i++) {
        struct client_s *client = vector_get(g->clients, i);
        if (client->is_closed || client->is_gui || client->team == NULL)
            continue;
        if (client->time > 0)
            client->time -= (g->lowest_time - tmp);
        if (client->food_time > 0)
            client->food_time -= (g->lowest_time - tmp);
        ai_starve_eat(g, client);
        printf("client%d->time: %d\n", client->client_nb, client->time);
        printf("client%d->food_time: %d\n", client->client_nb, client->food_time);
    }
    g->ressources_respawn -= (g->lowest_time - tmp);
}

int zappy_server(int ac, char **av)
{
    check_args(ac, av);
    srand(time(NULL));
    initialize_map();
    initialize_server();
    signal(SIGINT, sigint_handler);
    struct global_struct_s *g = get_global_struct();
    g->clients = vector_create(sizeof(struct client_s *));
    while (true) {
        printf("==========loop==========\n");
        set_fd_set(g);
        if (g->timeout.tv_sec == 0 && g->timeout.tv_usec == 0)
            g->null_timeout = true;
        printf("maxfd: %d\n", g->maxfd);
        printf("timeout: %ld s\n", g->timeout.tv_sec);
        printf("timeout: %ld us\n", g->timeout.tv_usec);
        printf("null_timeout: %d\n", g->null_timeout);
        int select_result = select(g->maxfd, &g->readset, NULL, NULL, (g->null_timeout) ? NULL : &g->timeout);
        g->null_timeout = false;
        printf("select_result: %d\n", select_result);
        remove_past_time(g);
        accept_new_client(select_result, g);
        manage_clients(select_result, g);
    }
    free_all();
    return 0;
}
