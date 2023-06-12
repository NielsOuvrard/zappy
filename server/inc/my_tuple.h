/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#pragma once
#include <stdlib.h>

struct my_tuple_s {
    void *first;
    void *second;
    void (*destroy_first)(void *);
    void (*destroy_second)(void *);
};

/*
** @brief Create a tuple object
** @return A pointer to the tuple object
*/
struct my_tuple_s *tuple_create(void);

/*
** @brief Initialize a tuple object
** @param this A pointer to the tuple object
*/
void tuple_init(struct my_tuple_s *this);

/*
** @brief Destroy a tuple object
** @param this A pointer to the tuple object
*/
void tuple_destroy(void *this);

/*
** @brief Set the first and second element of a tuple object
** @param this A pointer to the tuple object
** @param first A pointer to the first element
** @param second A pointer to the second element
** @param destroy_first A pointer to the function that destroy the first element
** @param destroy_second A pointer to the function that destroy the second element
*/
void tuple_set(struct my_tuple_s *this, void *first, void *second, void (*destroy_first)(void *), void (*destroy_second)(void *));

/*
** @brief Set the first element of a tuple object
** @param this A pointer to the tuple object
** @param first A pointer to the first element
*/
void tuple_set_first(struct my_tuple_s *this, void *first);

/*
** @brief Set the second element of a tuple object
** @param this A pointer to the tuple object
** @param second A pointer to the second element
*/
void tuple_set_second(struct my_tuple_s *this, void *second);

/*
** @brief Set the function that destroy the first element of a tuple object
** @param this A pointer to the tuple object
** @param destroy_first A pointer to the function that destroy the first element
*/
void tuple_set_destroy_first(struct my_tuple_s *this, void (*destroy_first)(void *));

/*
** @brief Set the function that destroy the second element of a tuple object
** @param this A pointer to the tuple object
** @param destroy_second A pointer to the function that destroy the second element
*/
void tuple_set_destroy_second(struct my_tuple_s *this, void (*destroy_second)(void *));

/*
** @brief Get the first element of a tuple object
** @param this A pointer to the tuple object
** @return A pointer to the first element
*/
void *tuple_get_first(struct my_tuple_s *this);

/*
** @brief Get the second element of a tuple object
** @param this A pointer to the tuple object
** @return A pointer to the second element
*/
void *tuple_get_second(struct my_tuple_s *this);

/*
** @brief Swap the first and second element of a tuple object
** @param this A pointer to the tuple object
*/
void tuple_swap(struct my_tuple_s *this);

/*
** @brief Print the first and second element of a tuple object
** @param this A pointer to the tuple object
** @param print_first A pointer to the function that print the first element
** @param print_second A pointer to the function that print the second element
*/
void tuple_print(struct my_tuple_s *this, void (*print_first)(void *), void (*print_second)(void *));