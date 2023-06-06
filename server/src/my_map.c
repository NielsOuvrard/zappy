/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "my_map.h"

struct my_map_s *map_create(void)
{
    struct my_map_s *this = malloc(sizeof(struct my_map_s));

    this->root = vector_create(sizeof(struct my_map_node_s));
    return this;
}

void map_init(struct my_map_s *this)
{
    this->root = vector_create(sizeof(struct my_map_node_s));
}

void map_destroy(struct my_map_s *this)
{
    vector_destroy(this->root, string_destroy);
    free(this);
}

int map_size(struct my_map_s *this)
{
    return vector_length(this->root);
}

void map_insert(struct my_map_s *this, struct my_string_s *key, struct my_string_s *value)
{
    struct my_map_node_s *node = malloc(sizeof(struct my_map_node_s));

    node->key = key;
    node->value = value;
    vector_push_back(this->root, node);
}

struct my_string_s *map_get(struct my_map_s *this, struct my_string_s *key)
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (string_equals(node->key, key->str))
            return node->value;
    }
    return NULL;
}

void map_remove(struct my_map_s *this, struct my_string_s *key)
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (string_equals(node->key, key->str)) {
            vector_remove(this->root, i);
            return;
        }
    }
}

void map_clear(struct my_map_s *this)
{
    vector_clear(this->root, string_destroy);
}

void map_set(struct my_map_s *this, struct my_string_s *key, struct my_string_s *value)
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (string_equals(node->key, key->str)) {
            string_destroy(node->value);
            node->value = value;
            return;
        }
    }
}

bool map_contains(struct my_map_s *this, struct my_string_s *key)
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (string_equals(node->key, key->str))
            return true;
    }
    return false;
}
