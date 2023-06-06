/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Mutex
*/

#include "Mutex.hpp"

void MyMutex::lock()
{
    mutex_.lock();
}

void MyMutex::unlock()
{
    mutex_.unlock();
}
