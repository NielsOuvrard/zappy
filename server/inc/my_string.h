/*
** EPITECH PROJECT, 2021
** zappy_server
** File description:
** zappy_server
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>

#include "my_vector.h"

struct string_s {
    char *str;
    int length;
    int capacity;
};

/**
** @brief Creates a string
** @return The created string
**/
struct string_s *string_create(void);

/**
** @brief Initializes the string
** @param this The string to initialize
**/
void string_init(struct string_s *this);

/**
** @brief Destroys the string
** @param this The string to destroy
**/
void string_destroy(void *this);

/**
** @brief Appends a string to another
** @param this The string to append to
** @param str The string to append
**/
void string_append(struct string_s *this, char *str);

/**
** @brief Append n char of a string to another
** @param this The string to append to
** @param str The string to append
** @param n The number of characters to append
**/
void string_append_n(struct string_s *this, char *str, int n);

/**
** @brief Appends an int to a string
** @param this The string to append to
** @param nb The int to append
**/
void string_append_int(struct string_s *this, int nb);

/**
** @brief Appends a float to a string
** @param this The string to append to
** @param nb The float to append
**/
void string_append_float(struct string_s *this, float nb);

/**
** @brief Appends a double to a string
** @param this The string to append to
** @param nb The double to append
**/
void string_append_double(struct string_s *this, double nb);

/**
** @brief Checks if a string is empty
** @param this The string to check
** @return true if empty, false otherwise
**/
bool string_isempty(struct string_s *this);

/**
** @brief Checks if is equal to a string
** @param this The string to check
** @param str The string to compare to
** @return true if equal, false otherwise
**/
bool string_equals(struct string_s *this, char *str);

/**
** @brief Checks if a string contains another
** @param this The string to check
** @param str The string to check for
** @return true if contains, false otherwise
**/
bool string_contains(struct string_s *this, char *str);

/**
** @brief Checks if a string starts with another
** @param this The string to check
** @param str The string to check for
** @return true if starts with, false otherwise
**/
bool string_startswith(struct string_s *this, char *str);

/**
** @brief Checks if a string ends with another
** @param this The string to check
** @param str The string to check for
** @return true if ends with, false otherwise
**/
bool string_endswith(struct string_s *this, char *str);

/**
** @brief Returns the index of a string in another
** @param this The string to check
** @param str The string to check for
** @return The index of the string, -1 if not found
**/
int string_indexof(struct string_s *this, char *str);

/**
** @brief Returns the last index of a string in another
** @param this The string to check
** @param str The string to check for
** @return The last index of the string, -1 if not found
**/
int string_lastindexof(struct string_s *this, char *str);

/**
** @brief Replaces a string with another
** @param this The string to replace in
** @param old The string to replace
** @param new The string to replace with
**/
void string_replace(struct string_s *this, char *old, char *new);

/**
** @brief Get the string as a char *
** @param this The string to get
** @return The string as a char *
**/
char *string_get(struct string_s *this);

/**
** @brief Get the string length
** @param this The string to get
** @return The string length
**/
int string_length(struct string_s *this);

/**
** @brief Get the string capacity
** @param this The string to get
** @return The string capacity
**/
int string_capacity(struct string_s *this);

/**
** @brief Clears the string
** @param this The string to clear
**/
void string_clear(struct string_s *this);

/**
** @brief Prints the string with a newline
** @param this The string to print
**/
void string_print_ln(struct string_s *this);

/**
** @brief Prints the string
** @param this The string to print
**/
void string_print(struct string_s *this);

/**
** @brief Prints the string in debug mode
** @param this The string to print
**/
void string_print_debug(struct string_s *this);

/**
** @brief Prints the string in debug mode with is length and capacity
** and a newline
** @param this The string to print
**/
void string_print_debug_info_ln(struct string_s *this);

/**
** @brief Gets a copy of the string as a char *
** @param this The string to get
** @return The string as a char *
**/
char *string_to_string(struct string_s *this);

/**
** @brief Gets a copy of the string as an int
** @param this The string to get
** @return The string as an int
**/
int string_to_int(struct string_s *this);

/**
** @brief Gets a copy of the string as a float
** @param this The string to get
** @return The string as a float
**/
float string_to_float(struct string_s *this);

/**
** @brief Gets a copy of the string as a double
** @param this The string to get
** @return The string as a double
**/
double string_to_double(struct string_s *this);

/**
** @brief Generates a string from another
** @param this The string to copy
** @return The new string
**/
struct string_s *string_copy(struct string_s *this);

/**
** @brief Generates a string from a char *
** @param str The string to copy
** @return The new string
**/
struct string_s *string_from_string(char *str);

/**
** @brief Generates a string from an int
** @param nb The int to copy
** @return The new string
**/
struct string_s *string_from_int(int nb);

/**
** @brief Generates a string from a float
** @param nb The float to copy
** @return The new string
**/
struct string_s *string_from_float(float nb);

/**
** @brief Generates a string from a double
** @param nb The double to copy
** @return The new string
**/
struct string_s *string_from_double(double nb);

/**
** @brief Generates a string from a format
** @param format The format to copy
** @return The new string
**/
struct string_s *string_from_format(char *format, ...);

/**
** @brief Gets a char at an index
** @param this The string to get
** @param index The index to get
** @return The char
**/
char string_get_at(struct string_s *this, int index);

/**
** @brief Sets a char at an index
** @param this The string to set
** @param index The index to set
** @param c The char to set
**/
void string_set_at(struct string_s *this, int index, char c);

/**
** @brief Inserts a char at an index
** @param this The string to insert in
** @param index The index to insert at
** @param c The char to insert
**/
void string_insert_at(struct string_s *this, int index, char c);

/**
** @brief Removes a char at an index
** @param this The string to remove in
** @param index The index to remove at
**/
void string_remove_at(struct string_s *this, int index);

/**
** @brief Return a substring of a string
** @param this The string to get the substring from
** @param start The start index
** @param end The end index
** @return The substring
**/
struct string_s *string_substring(struct string_s *this, int start, int end);






// TODO: Add these functions

/**
** @brief Splits a string into an array
** @param this The string to split
** @param delim The delimiter to split with
** @return The array of strings
**/
struct vector_s *string_split(struct string_s *this, char *delim);

/**
** @brief Joins an array of strings into a string
** @param this The array of strings
** @param delim The delimiter to join with
** @return The string
**/
struct string_s *string_join(struct vector_s *strs, char *delim);
