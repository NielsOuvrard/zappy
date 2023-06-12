/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "my_tuple.h"

struct my_tuple_s *tuple_create(void)
{
    struct my_tuple_s *this = malloc(sizeof(struct my_tuple_s));

    this->first = NULL;
    this->second = NULL;
    this->destroy_first = NULL;
    this->destroy_second = NULL;
    return this;
}

void tuple_init(struct my_tuple_s *this)
{
    this->first = NULL;
    this->second = NULL;
}

void tuple_destroy(void *this)
{
    struct my_tuple_s *tuple = (struct my_tuple_s *)this;

    if (tuple->destroy_first)
        tuple->destroy_first(tuple->first);
    if (tuple->destroy_second)
        tuple->destroy_second(tuple->second);
    free(tuple);
}

void tuple_set(struct my_tuple_s *this, void *first, void *second, void (*destroy_first)(void *), void (*destroy_second)(void *))
{
    if (this->destroy_first)
        this->destroy_first(this->first);
    if (this->destroy_second)
        this->destroy_second(this->second);
    this->first = first;
    this->second = second;
    this->destroy_first = destroy_first;
    this->destroy_second = destroy_second;
}

void tuple_set_first(struct my_tuple_s *this, void *first)
{
    if (this->destroy_first)
        this->destroy_first(this->first);
    this->first = first;
}

void tuple_set_second(struct my_tuple_s *this, void *second)
{
    if (this->destroy_second)
        this->destroy_second(this->second);
    this->second = second;
}

void tuple_set_destroy_first(struct my_tuple_s *this, void (*destroy_first)(void *))
{
    this->destroy_first = destroy_first;
}

void tuple_set_destroy_second(struct my_tuple_s *this, void (*destroy_second)(void *))
{
    this->destroy_second = destroy_second;
}

void *tuple_get_first(struct my_tuple_s *this)
{
    return this->first;
}

void *tuple_get_second(struct my_tuple_s *this)
{
    return this->second;
}

void tuple_swap(struct my_tuple_s *this)
{
    void *tmp = this->first;

    this->first = this->second;
    this->second = tmp;
}

void tuple_print(struct my_tuple_s *this, void (*print_first)(void *), void (*print_second)(void *))
{
    if (print_first)
        print_first(this->first);
    if (print_second)
        print_second(this->second);
}
