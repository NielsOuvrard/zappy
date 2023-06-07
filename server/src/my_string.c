/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#include "my_string.h"

struct my_string_s *string_create(void)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));

    this->str = malloc(sizeof(char) * 1);
    this->str[0] = '\0';
    this->length = 0;
    this->capacity = 1;
    return this;
}

void string_init(struct my_string_s *this)
{
    this->str = malloc(sizeof(char) * 1);
    this->str[0] = '\0';
    this->length = 0;
    this->capacity = 1;
}

void string_destroy(void *this)
{
    struct my_string_s *string = this;
    free(string->str);
    free(string);
}

void string_append(struct my_string_s *this, char *str)
{
    int len = strlen(str);

    // check if we need to resize
    // if yes double the capacity until it fits
    while (this->length + len + 1 > this->capacity) {
        this->capacity *= 2;
        this->str = realloc(this->str, this->capacity);
    }
    // append the string
    strcat(this->str, str);
    this->length += len;
}

void string_append_n(struct my_string_s *this, char *str, int n)
{
    int len = strlen(str);

    if (n > len)
        n = len;
    // check if we need to resize
    // if yes double the capacity until it fits
    while (this->length + n + 1 > this->capacity) {
        this->capacity *= 2;
        this->str = realloc(this->str, this->capacity);
    }
    // append the string
    strncat(this->str, str, n);
    this->length += n;
}

void string_append_int(struct my_string_s *this, int nb)
{
    char str[12];

    sprintf(str, "%d", nb);
    string_append(this, str);
}

void string_append_float(struct my_string_s *this, float nb)
{
    char str[12];

    sprintf(str, "%f", nb);
    string_append(this, str);
}

void string_append_double(struct my_string_s *this, double nb)
{
    char str[12];

    sprintf(str, "%f", nb);
    string_append(this, str);
}

bool string_isempty(void *this)
{
    struct my_string_s *string = this;
    return string->length == 0;
}

bool string_equals(void *this, void *str)
{
    struct my_string_s *first = this;
    char *second = str;
    return strcmp(first->str, second) == 0;
}

bool string_equals_str(void *this, void *str)
{
    struct my_string_s *first = this;
    struct my_string_s *second = str;
    return strcmp(first->str, second->str) == 0;
}

bool string_contains(void *this, void *str)
{
    struct my_string_s *first = this;
    char *second = str;
    return strstr(first->str, second) != NULL;
}

bool string_startswith(void *this, void *str)
{
    struct my_string_s *first = this;
    char *second = str;
    return strncmp(first->str, second, strlen(second)) == 0;
}

bool string_endswith(void *this, void *str)
{
    struct my_string_s *first = this;
    char *second = str;
    int len = strlen(second);
    int start = first->length - len;

    if (start < 0)
        return 0;
    return strncmp(first->str + start, second, len) == 0;
}

int string_indexof(struct my_string_s *this, char *str)
{
    char *ptr = strstr(this->str, str);

    if (ptr == NULL)
        return -1;
    return ptr - this->str;
}

int string_lastindexof(struct my_string_s *this, char *str)
{
    char *ptr = strstr(this->str, str);
    char *last = NULL;

    while (ptr != NULL) {
        last = ptr;
        ptr = strstr(ptr + 1, str);
    }
    if (last == NULL)
        return -1;
    return last - this->str;
}

void string_replace(struct my_string_s *this, char *old, char *new)
{
    int old_len = strlen(old);
    int new_len = strlen(new);
    int index = string_indexof(this, old);

    while (index != -1) {
        // check if we need to resize
        // if yes double the capacity until it fits
        while (this->length + new_len - old_len + 1 > this->capacity) {
            this->capacity *= 2;
            this->str = realloc(this->str, this->capacity);
        }
        // move the string to the right
        memmove(this->str + index + new_len, this->str + index + old_len,
            this->length - index - old_len + 1);
        // replace the string
        memcpy(this->str + index, new, new_len);
        this->length += new_len - old_len;
        index = string_indexof(this, old);
    }
}

char *string_get(struct my_string_s *this)
{
    return this->str;
}

int string_length(struct my_string_s *this)
{
    return this->length;
}

int string_capacity(struct my_string_s *this)
{
    return this->capacity;
}

void string_clear(struct my_string_s *this)
{
    free(this->str);
    string_init(this);
}

void string_print_ln(struct my_string_s *this)
{
    printf("%s\n", this->str);
}

void string_print(struct my_string_s *this)
{
    printf("%s", this->str);
}

void string_print_debug(struct my_string_s *this)
{
    printf("string: %s\n", this->str);
}

void string_print_debug_info_ln(struct my_string_s *this)
{
    printf("string: %s\n", this->str);
    printf("length: %d\n", this->length);
    printf("capacity: %d\n", this->capacity);
    printf("\n");
}

char *string_to_string(struct my_string_s *this)
{
    char *str = malloc(sizeof(char) * (this->length + 1));

    strcpy(str, this->str);
    return str;
}

int string_to_int(struct my_string_s *this)
{
    return atoi(this->str);
}

float string_to_float(struct my_string_s *this)
{
    return atof(this->str);
}

double string_to_double(struct my_string_s *this)
{
    return atof(this->str);
}

struct my_string_s *string_copy(struct my_string_s *this)
{
    struct my_string_s *copy = malloc(sizeof(struct my_string_s));

    string_init(copy);
    string_append(copy, this->str);
    return copy;
}

struct my_string_s *string_from_string(char *str)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));

    string_init(this);
    string_append(this, str);
    return this;
}

struct my_string_s *string_from_int(int nb)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));

    string_init(this);
    string_append_int(this, nb);
    return this;
}

struct my_string_s *string_from_float(float nb)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));

    string_init(this);
    string_append_float(this, nb);
    return this;
}

struct my_string_s *string_from_double(double nb)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));

    string_init(this);
    string_append_double(this, nb);
    return this;
}

void string_append_format(struct my_string_s *this, char *format, va_list args)
{
    int size = vsnprintf(NULL, 0, format, args);

    while (this->length + size + 1 > this->capacity) {
        this->capacity *= 2;
        this->str = realloc(this->str, this->capacity);
    }
    vsprintf(this->str + this->length, format, args);
    this->length += size;
}

struct my_string_s *string_from_format(char *format, ...)
{
    struct my_string_s *this = malloc(sizeof(struct my_string_s));
    va_list args;

    string_init(this);
    va_start(args, format);
    string_append_format(this, format, args);
    va_end(args);
    return this;
}

char string_get_at(struct my_string_s *this, int index)
{
    return this->str[index];
}

void string_set_at(struct my_string_s *this, int index, char c)
{
    this->str[index] = c;
}

void string_insert_at(struct my_string_s *this, int index, char c)
{
    if (index < 0 || index > this->length)
        return;
    if (this->length + 1 > this->capacity) {
        this->capacity *= 2;
        this->str = realloc(this->str, this->capacity);
    }
    memmove(this->str + index + 1, this->str + index,
    this->length - index + 1);
    this->str[index] = c;
    this->length++;
}

void string_remove_at(struct my_string_s *this, int index)
{
    if (index < 0 || index >= this->length)
        return;
    memmove(this->str + index, this->str + index + 1, this->length - index);
    this->length--;
}

struct my_string_s *string_substring(struct my_string_s *this, int start, int end)
{
    struct my_string_s *str = malloc(sizeof(struct my_string_s));

    string_init(str);
    if (end > this->length)
        end = this->length;
    if (start < 0 || start >= this->length || end < 0)
        return str;
    if (start > end) {
        int tmp = start;

        start = end;
        end = tmp;
    }
    string_append_n(str, this->str + start, end - start);
    return str;
}

struct my_vector_s *string_split(struct my_string_s *this, char *delimiter)
{
    struct my_vector_s *vector = malloc(sizeof(struct my_vector_s));
    char *str = this->str;
    char *token = strtok(str, delimiter);

    vector_init(vector, sizeof(struct my_string_s));
    while (token != NULL) {
        vector_push_back(vector, string_from_string(token));
        token = strtok(NULL, delimiter);
    }
    return vector;
}

struct my_string_s *string_join(struct my_vector_s *vector, char *delimiter)
{
    struct my_string_s *str = malloc(sizeof(struct my_string_s));
    int i = 0;

    string_init(str);
    for (i = 0; i < vector->length; i++) {
        string_append(str, ((struct my_string_s *)vector->items[i])->str);
        if (i < vector->length - 1)
            string_append(str, delimiter);
    }
    return str;
}
