/*
** EPITECH PROJECT, 2023
** B-CCP-400-MAR-4-1-theplazza-niels.ouvrard
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
