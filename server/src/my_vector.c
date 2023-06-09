/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "my_vector.h"

struct my_vector_s *vector_create(size_t item_size)
{
    struct my_vector_s *this = malloc(sizeof(struct my_vector_s));

    this->capacity = 1;
    this->length = 0;
    this->item_size = item_size;
    this->items = malloc(sizeof(this->item_size) * this->capacity);
    return this;
}

void vector_init(struct my_vector_s *this, size_t item_size)
{
    this->capacity = 1;
    this->length = 0;
    this->item_size = item_size;
    this->items = malloc(sizeof(this->item_size) * this->capacity);
}

void vector_destroy(struct my_vector_s *this, void (*destructor)(void *))
{
    if (destructor) {
        for (int i = 0; i < this->length; i++)
            destructor(this->items[i]);
    }
    free(this->items);
    free(this);
}

int vector_length(struct my_vector_s *this)
{
    return this->length;
}

void vector_resize(struct my_vector_s *this, int new_capacity)
{
    this->capacity = new_capacity;
    this->items = realloc(this->items,
    sizeof(this->item_size) * this->capacity);
}

void vector_push_back(struct my_vector_s *this, void *item)
{
    // check if we need to resize
    // if yes double the capacity until it fits
    while (this->length + 1 > this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items,
        sizeof(this->item_size) * this->capacity);
    }
    // append the item
    this->items[this->length] = item;
    this->length++;
}

void *vector_pop_back(struct my_vector_s *this)
{
    void *item = this->items[this->length - 1];

    this->length--;
    return item;
}

void vector_set(struct my_vector_s *this, int index, void *item, void (*destructor)(void *))
{
    if (index < 0 || index >= this->length) {
        dprintf(2, "Vector: Index out of bounds\n");
        return;
    }
    if (destructor)
        destructor(this->items[index]);
    this->items[index] = item;
}

void *vector_get(struct my_vector_s *this, int index)
{
    if (index < 0 || index >= this->length) {
        dprintf(2, "Vector: Index out of bounds\n");
        return NULL;
    }
    return this->items[index];
}

void vector_insert(struct my_vector_s *this, int index, void *item)
{
    if (index < 0 || index >= this->length) {
        dprintf(2, "Vector: Index out of bounds\n");
        return;
    }
    // check if we need to resize
    // if yes double the capacity until it fits
    while (this->length + 1 > this->capacity) {
        this->capacity *= 2;
        this->items = realloc(this->items,
        sizeof(this->item_size) * this->capacity);
    }
    // shift all items to the right
    for (int i = this->length; i > index; i--)
        this->items[i] = this->items[i - 1];
    // insert the item
    this->items[index] = item;
    this->length++;
}

void *vector_remove(struct my_vector_s *this, int index)
{
    void *item;

    if (index < 0 || index >= this->length) {
        dprintf(2, "Vector: Index out of bounds\n");
        return NULL;
    }
    item = this->items[index];
    // shift all items to the left
    for (int i = index; i < this->length - 1; i++)
        this->items[i] = this->items[i + 1];
    this->length--;
    return item;
}

void vector_clear(struct my_vector_s *this, void (*destructor)(void *))
{
    vector_destroy(this, destructor);
    vector_init(this, this->item_size);
}

void vector_sort(struct my_vector_s *this, int (*cmp)(void *, void *))
{
    void *tmp;

    for (int i = 0; i < this->length; i++) {
        for (int j = i + 1; j < this->length; j++) {
            if (cmp(this->items[i], this->items[j]) > 0) {
                tmp = this->items[i];
                this->items[i] = this->items[j];
                this->items[j] = tmp;
            }
        }
    }
}

void vector_foreach(struct my_vector_s *this, void (*func)(void *))
{
    for (int i = 0; i < this->length; i++)
        func(this->items[i]);
}
