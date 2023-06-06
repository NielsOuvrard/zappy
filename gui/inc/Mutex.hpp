/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Mutex
*/

#pragma once

#include <mutex>

class MyMutex
{
public:
    void lock();
    void unlock();

private:
    std::mutex mutex_;
};
