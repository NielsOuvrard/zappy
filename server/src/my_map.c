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

void node_destroy(void *this, void (*destroy_key)(void *), void (*destroy_value)(void *))
{
    struct my_map_node_s *node = this;

    if (!node)
        return;
    if (destroy_key)
        destroy_key(node->key);
    if (destroy_value)
        destroy_value(node->value);
    free(node);
}

void map_destroy(struct my_map_s *this, void (*destroy_key)(void *), void (*destroy_value)(void *))
{
    for (int i = 0; i < this->root->length; i++)
        node_destroy(this->root->items[i], destroy_key, destroy_value);
    free(this->root->items);
    free(this->root);
    free(this);
}

int map_size(struct my_map_s *this)
{
    return vector_length(this->root);
}

void map_insert(struct my_map_s *this, void *key, void *value)
{
    struct my_map_node_s *node = malloc(sizeof(struct my_map_node_s));

    node->key = key;
    node->value = value;
    vector_push_back(this->root, node);
}

void *map_get(struct my_map_s *this, void *key, bool (*cmp)(void *, void *))
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (cmp(node->key, key))
            return node->value;
    }
    return NULL;
}

void map_remove(struct my_map_s *this, void *key, bool (*cmp)(void *, void *), void (*destroy_key)(void *), void (*destroy_value)(void *))
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (cmp(node->key, key)) {
            struct my_map_node_s *tmp = vector_remove(this->root, i);
            node_destroy(tmp, destroy_key, destroy_value);
            return;
        }
    }
}

void map_clear(struct my_map_s *this, void (*destroy_key)(void *), void (*destroy_value)(void *))
{
    for (int i = 0; i < this->root->length; i++)
        node_destroy(this->root->items[i], destroy_key, destroy_value);
    free(this->root->items);
    free(this->root);
    this->root = vector_create(sizeof(struct my_map_node_s));
}

void map_set(struct my_map_s *this, void *key, void *value, bool (*cmp)(void *, void *), void (*destroy_value)(void *))
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (cmp(node->key, key)) {
            if (destroy_value)
                destroy_value(node->value);
            node->value = value;
            return;
        }
    }
}

bool map_contains(struct my_map_s *this, void *key, bool (*cmp)(void *, void *))
{
    struct my_map_node_s *node = NULL;

    for (int i = 0; i < this->root->length; i++) {
        node = vector_get(this->root, i);
        if (cmp(node->key, key))
            return true;
    }
    return false;
}
