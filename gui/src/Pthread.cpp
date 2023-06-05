/*
** EPITECH PROJECT, 2023
** B-CCP-400-MAR-4-1-theplazza-niels.ouvrard
** File description:
** Pthread
*/

#include "Pthread.hpp"

MyPthread::MyPthread()
{
    attr_ = {};
    pthread_attr_init(&attr_);
}

MyPthread::~MyPthread()
{
    pthread_attr_destroy(&attr_);
}

void MyPthread::create(void *(*startRoutine)(void *), void *arg)
{
    pthread_create(&thread_, &attr_, startRoutine, arg);
}

void MyPthread::join()
{
    pthread_join(thread_, NULL);
}

void MyPthread::cancel()
{
    pthread_cancel(thread_);
}

void MyPthread::exit(void *valuePtr)
{
    pthread_exit(valuePtr);
}

void MyPthread::detach()
{
    pthread_detach(thread_);
}

pthread_t MyPthread::getThread() const
{
    return thread_;
}

pthread_attr_t MyPthread::getAttr() const
{
    return attr_;
}
