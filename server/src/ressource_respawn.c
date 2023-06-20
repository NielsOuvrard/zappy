/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

int *get_food(struct tile_s *tile)
{
    return (&tile->food);
}

int *get_linemate(struct tile_s *tile)
{
    return (&tile->linemate);
}

int *get_deraumere(struct tile_s *tile)
{
    return (&tile->deraumere);
}

int *get_sibur(struct tile_s *tile)
{
    return (&tile->sibur);
}

int *get_mendiane(struct tile_s *tile)
{
    return (&tile->mendiane);
}

int *get_phiras(struct tile_s *tile)
{
    return (&tile->phiras);
}

int *get_thystame(struct tile_s *tile)
{
    return (&tile->thystame);
}

void add_ressource(struct global_struct_s *g, int to_add, int *(*get_ressource)(struct tile_s *))
{
    while (to_add > 0) {
        int x = rand() % g->arg->width;
        int y = rand() % g->arg->height;
        struct tile_s *tile = vector_get(vector_get(g->map, y), x);
        if (*get_ressource(tile) <= 0) {
            *get_ressource(tile) += 1;
            to_add--;
            // GUI Event
            struct my_string_s *current_tile = string_from_format("bct %d %d %d %d %d %d %d %d %d\n",
            x, y, tile->food, tile->linemate, tile->deraumere,
            tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
            send_to_all_gui(g, current_tile->str);
            string_destroy(current_tile);
        }
    }
}

void ressoure_respawn(void)
{
    struct global_struct_s *g = get_global_struct();
    g->ressources_respawn = RESSOURCES_RESPAWN_TIME;
    printf("Respawn ressources\n");

    // get actual ressources
    int actual_food = 0;
    int actual_linemate = 0;
    int actual_deraumere = 0;
    int actual_sibur = 0;
    int actual_mendiane = 0;
    int actual_phiras = 0;
    int actual_thystame = 0;
    for (int y = 0; y < g->arg->height; y++) {
        for (int x = 0; x < g->arg->width; x++) {
            struct tile_s *tile = vector_get(vector_get(g->map, y), x);
            actual_food += tile->food;
            actual_linemate += tile->linemate;
            actual_deraumere += tile->deraumere;
            actual_sibur += tile->sibur;
            actual_mendiane += tile->mendiane;
            actual_phiras += tile->phiras;
            actual_thystame += tile->thystame;
        }
    }

    // respawn FOOD if needed
    int max_food = (g->arg->width * g->arg->height) * 0.5;
    int missing_food = max_food - actual_food;
    add_ressource(g, missing_food, get_food);
    // respawn LINEMATE if needed
    int max_linemate = (g->arg->width * g->arg->height) * 0.3;
    int missing_linemate = max_linemate - actual_linemate;
    add_ressource(g, missing_linemate, get_linemate);
    // respawn DERAUMERE if needed
    int max_deraumere = (g->arg->width * g->arg->height) * 0.15;
    int missing_deraumere = max_deraumere - actual_deraumere;
    add_ressource(g, missing_deraumere, get_deraumere);
    // respawn SIBUR if needed
    int max_sibur = (g->arg->width * g->arg->height) * 0.1;
    int missing_sibur = max_sibur - actual_sibur;
    add_ressource(g, missing_sibur, get_sibur);
    // respawn MENDIANE if needed
    int max_mendiane = (g->arg->width * g->arg->height) * 0.1;
    int missing_mendiane = max_mendiane - actual_mendiane;
    add_ressource(g, missing_mendiane, get_mendiane);
    // respawn PHIRAS if needed
    int max_phiras = (g->arg->width * g->arg->height) * 0.08;
    int missing_phiras = max_phiras - actual_phiras;
    add_ressource(g, missing_phiras, get_phiras);
    // respawn THYSTAME if needed
    int max_thystame = (g->arg->width * g->arg->height) * 0.05;
    int missing_thystame = max_thystame - actual_thystame;
    add_ressource(g, missing_thystame, get_thystame);
}
