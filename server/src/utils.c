/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

void convert_coordinate(int *x, int *y)
{
    struct global_struct_s *global_struct = get_global_struct();
    struct arg_s *arg = global_struct->arg;
    *x = *x % arg->width;
    *y = *y % arg->height;
    while (*x < 0)
        *x = arg->width + *x;
    while (*y < 0)
        *y = arg->height + *y;
}