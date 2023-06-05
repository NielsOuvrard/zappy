/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "zappy_server.h"

struct arg_s *get_arg(void)
{
    static struct arg_s arg;
    return &arg;
}

struct global_struct_s *get_global_struct(void)
{
    static struct global_struct_s global_struct;
    return &global_struct;
}
