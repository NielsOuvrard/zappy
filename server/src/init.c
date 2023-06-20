/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

struct my_vector_s *generate_incantation_need(struct global_struct_s *g)
{
    struct my_vector_s *need = vector_create(sizeof(struct incant_s *));
    struct incant_s *lvl_1 = malloc(sizeof(struct incant_s));
    lvl_1->level = 1;
    lvl_1->nb_players = 1;
    lvl_1->linemate = 1;
    lvl_1->deraumere = 0;
    lvl_1->sibur = 0;
    lvl_1->mendiane = 0;
    lvl_1->phiras = 0;
    lvl_1->thystame = 0;
    vector_push_back(need, lvl_1);
    struct incant_s *lvl_2 = malloc(sizeof(struct incant_s));
    lvl_2->level = 2;
    lvl_2->nb_players = 2;
    lvl_2->linemate = 1;
    lvl_2->deraumere = 1;
    lvl_2->sibur = 1;
    lvl_2->mendiane = 0;
    lvl_2->phiras = 0;
    lvl_2->thystame = 0;
    vector_push_back(need, lvl_2);
    struct incant_s *lvl_3 = malloc(sizeof(struct incant_s));
    lvl_3->level = 3;
    lvl_3->nb_players = 2;
    lvl_3->linemate = 2;
    lvl_3->deraumere = 0;
    lvl_3->sibur = 1;
    lvl_3->mendiane = 0;
    lvl_3->phiras = 2;
    lvl_3->thystame = 0;
    vector_push_back(need, lvl_3);
    struct incant_s *lvl_4 = malloc(sizeof(struct incant_s));
    lvl_4->level = 4;
    lvl_4->nb_players = 4;
    lvl_4->linemate = 1;
    lvl_4->deraumere = 1;
    lvl_4->sibur = 2;
    lvl_4->mendiane = 0;
    lvl_4->phiras = 1;
    lvl_4->thystame = 0;
    vector_push_back(need, lvl_4);
    struct incant_s *lvl_5 = malloc(sizeof(struct incant_s));
    lvl_5->level = 5;
    lvl_5->nb_players = 4;
    lvl_5->linemate = 1;
    lvl_5->deraumere = 2;
    lvl_5->sibur = 1;
    lvl_5->mendiane = 3;
    lvl_5->phiras = 0;
    lvl_5->thystame = 0;
    vector_push_back(need, lvl_5);
    struct incant_s *lvl_6 = malloc(sizeof(struct incant_s));
    lvl_6->level = 6;
    lvl_6->nb_players = 6;
    lvl_6->linemate = 1;
    lvl_6->deraumere = 2;
    lvl_6->sibur = 3;
    lvl_6->mendiane = 0;
    lvl_6->phiras = 1;
    lvl_6->thystame = 0;
    vector_push_back(need, lvl_6);
    struct incant_s *lvl_7 = malloc(sizeof(struct incant_s));
    lvl_7->level = 7;
    lvl_7->nb_players = 6;
    lvl_7->linemate = 2;
    lvl_7->deraumere = 2;
    lvl_7->sibur = 2;
    lvl_7->mendiane = 2;
    lvl_7->phiras = 2;
    lvl_7->thystame = 1;
    vector_push_back(need, lvl_7);
    vector_set_destructor(need, free);
    return (need);
}

void initialize_map(void)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    global_struct->incant_need = generate_incantation_need(global_struct);
    global_struct->client_id = 0;
    global_struct->egg_id = 0;
    global_struct->ai_spawn = false;
    global_struct->ressources_respawn = RESSOURCES_RESPAWN_TIME;
    global_struct->map = vector_create(sizeof(struct my_vector_s *));
    for (int i = 0; i < arg->height; i++) {
        struct my_vector_s *line = vector_create(sizeof(struct my_string_s *));
        for (int j = 0; j < arg->width; j++) {
            struct tile_s *tile = malloc(sizeof(struct tile_s));
            tile->food = 0;
            tile->linemate = 0;
            tile->deraumere = 0;
            tile->sibur = 0;
            tile->mendiane = 0;
            tile->phiras = 0;
            tile->thystame = 0;
            vector_push_back(line, tile);
        }
        vector_set_destructor(line, free);
        vector_push_back(global_struct->map, line);
    }
    global_struct->null_timeout = false;
    global_struct->eggs = vector_create(sizeof(struct egg_s *));
    for (int i = 0; i < arg->clientsNb * vector_length(arg->names); i++) {
        struct egg_s *egg = malloc(sizeof(struct egg_s));
        egg->id = global_struct->egg_id++;
        egg->posx = rand() % arg->width;
        egg->posy = rand() % arg->height;
        egg->hatch_time = 0;
        egg->is_hatched = true;
        egg->is_forked = false;
        egg->orientation = rand() % 4 + 1;
        egg->team = string_copy(vector_get(arg->names, i % vector_length(arg->names)));
        vector_push_back(global_struct->eggs, egg);
    }
    int max_food = (arg->width * arg->height) * 0.5;
    int max_linemate = (arg->width * arg->height) * 0.3;
    int max_deraumere = (arg->width * arg->height) * 0.15;
    int max_sibur = (arg->width * arg->height) * 0.1;
    int max_mendiane = (arg->width * arg->height) * 0.1;
    int max_phiras = (arg->width * arg->height) * 0.08;
    int max_thystame = (arg->width * arg->height) * 0.05;
    int max_all = max_food + max_linemate + max_deraumere +
    max_sibur + max_mendiane + max_phiras + max_thystame;
    while (max_all) {
        int x = rand() % arg->width;
        int y = rand() % arg->height;
        int r = rand() % 7;
        struct tile_s *tile = vector_get(vector_get(global_struct->map, y), x);
        if (r == 0 && max_food > 0 && tile->food <= 0) {
            tile->food++;
            max_food--;
            max_all--;
        }
        if (r == 1 && max_linemate > 0 && tile->linemate <= 0) {
            tile->linemate++;
            max_linemate--;
            max_all--;
        }
        if (r == 2 && max_deraumere > 0 && tile->deraumere <= 0) {
            tile->deraumere++;
            max_deraumere--;
            max_all--;
        }
        if (r == 3 && max_sibur > 0 && tile->sibur <= 0) {
            tile->sibur++;
            max_sibur--;
            max_all--;
        }
        if (r == 4 && max_mendiane > 0 && tile->mendiane <= 0) {
            tile->mendiane++;
            max_mendiane--;
            max_all--;
        }
        if (r == 5 && max_phiras > 0 && tile->phiras <= 0) {
            tile->phiras++;
            max_phiras--;
            max_all--;
        }
        if (r == 6 && max_thystame > 0 && tile->thystame <= 0) {
            tile->thystame++;
            max_thystame--;
            max_all--;
        }
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
    server->server_addr = (struct sockaddr_in) {0};
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
