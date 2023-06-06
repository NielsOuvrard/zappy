/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Pthread
*/

#pragma once
#include <pthread.h>
#include <iostream>

class MyPthread
{
private:
    pthread_t thread_;
    pthread_attr_t attr_;
    // void *(*_start_routine)(void *);

public:
    MyPthread();
    ~MyPthread();

    void create(void *(*startRoutine)(void *), void *arg);
    void join();
    void cancel();
    void exit(void *valuePtr);
    void detach();
    // void setRoutine(void *(*__start_routine)(void *));
    pthread_t getThread() const;
    pthread_attr_t getAttr() const;
};
