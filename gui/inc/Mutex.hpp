/*
** EPITECH PROJECT, 2023
** B-CCP-400-MAR-4-1-theplazza-niels.ouvrard
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
