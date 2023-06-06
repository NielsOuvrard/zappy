/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#pragma once
#include <stdbool.h>

#include "my_vector.h"
#include "my_string.h"

struct my_map_node_s {
    struct my_string_s *key;
    struct my_string_s *value;
};

struct my_map_s {
    struct my_vector_s *root;
};

/*
** @brief Create a new map
** @return A pointer to the new map
*/
struct my_map_s *map_create(void);

/*
** @brief Initialize a map
** @param this A pointer to the map to initialize
*/
void map_init(struct my_map_s *this);

/*
** @brief Destroy a map
** @param this A pointer to the map to destroy
*/
void map_destroy(struct my_map_s *this);

/*
** @brief Get the size of a map
** @param this A pointer to the map
** @return The size of the map
*/
int map_size(struct my_map_s *this);

/*
** @brief Insert a new element in a map
** @param this A pointer to the map
** @param key A pointer to the key
** @param value A pointer to the value
*/
void map_insert(struct my_map_s *this, struct my_string_s *key, struct my_string_s *value);

/*
** @brief Get a value from a map
** @param this A pointer to the map
** @param key A pointer to the key
** @return A pointer to the value
*/
struct my_string_s *map_get(struct my_map_s *this, struct my_string_s *key);

/*
** @brief Remove an element from a map
** @param this A pointer to the map
** @param key A pointer to the key
*/
void map_remove(struct my_map_s *this, struct my_string_s *key);

/*
** @brief Clear a map
** @param this A pointer to the map
*/
void map_clear(struct my_map_s *this);

/*
** @brief Set a value in a map
** @param this A pointer to the map
** @param key A pointer to the key
** @param value A pointer to the value
*/
void map_set(struct my_map_s *this, struct my_string_s *key, struct my_string_s *value);

/*
** @brief Check if a map contains a key
** @param this A pointer to the map
** @param key A pointer to the key
** @param cmp A pointer to the compare function
** @return true if the map contains the key, false otherwise
*/
bool map_contains(struct my_map_s *this, struct my_string_s *key);
