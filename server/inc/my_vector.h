/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>

struct my_vector_s {
    void **items;
    int capacity;
    int length;
    size_t item_size;
    void (*destructor)(void *);
};

/**
** @brief Creates a vector.
** @param item_size The size of the items in the vector.
** @return The created vector.
**/
struct my_vector_s *vector_create(size_t item_size);

/**
** @brief Initializes a vector.
** @param vector The vector to initialize.
**/
void vector_init(struct my_vector_s *vector, size_t item_size);

/**
** @brief Sets the destructor of a vector.
** @param vector The vector to set the destructor of.
** @param destructor The destructor to set.
**/
void vector_set_destructor(struct my_vector_s *vector, void (*destructor)(void *));

/**
** @brief Destroys a vector.
** @param vector The vector to destroy.
**/
void vector_destroy(struct my_vector_s *vector);

/**
** @brief Returns the length of a vector.
** @param vector The vector to get the length of.
** @return The length of the vector.
**/
int vector_length(struct my_vector_s *vector);

/**
** @brief Resizes a vector.
** @param vector The vector to resize.
** @param capacity The new capacity of the vector.
**/
void vector_resize(struct my_vector_s *vector, int capacity);

/**
** @brief Adds an item to the end of a vector.
** @param vector The vector to add the item to.
** @param item The item to add to the vector.
**/
void vector_push_back(struct my_vector_s *vector, void *item);

/**
** @brief Removes an item from the end of a vector.
** @param vector The vector to remove the item from.
** @return The item removed from the vector.
**/
void *vector_pop_back(struct my_vector_s *vector);

/**
** @brief Sets an item in a vector.
** @param vector The vector to set the item in.
** @param index The index of the item to set.
** @param item The item to set.
**/
void vector_set(struct my_vector_s *vector, int index, void *item);

/**
** @brief Gets an item from a vector.
** @param vector The vector to get the item from.
** @param index The index of the item to get.
** @return The item at the index in the vector.
**/
void *vector_get(struct my_vector_s *vector, int index);

/**
** @brief Inserts an item into a vector.
** @param vector The vector to insert the item into.
** @param index The index to insert the item at.
** @param item The item to insert.
**/
void vector_insert(struct my_vector_s *vector, int index, void *item);

/**
** @brief Removes an item from a vector.
** @param vector The vector to remove the item from.
** @param index The index of the item to remove.
** @return The item removed from the vector.
**/
void *vector_remove(struct my_vector_s *vector, int index);

/**
** @brief Clears a vector.
** @param vector The vector to clear.
**/
void vector_clear(struct my_vector_s *vector);

/**
** @brief Sorts a vector.
** @param vector The vector to sort.
** @param cmp The comparison function to use.
**/
void vector_sort(struct my_vector_s *vector, int (*cmp)(void *, void *));

/**
** @brief Iterates over a vector.
** @param vector The vector to iterate over.
** @param func The function to call on each item.
**/
void vector_foreach(struct my_vector_s *vector, void (*func)(void *));
