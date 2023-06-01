/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

// sfml
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int zappy_gui(int ac, char **av);

enum class ZappyGuiState
{
    MENU,
    GAME,
    END
};

enum class resource
{
    food,
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame
};

// ? useless
enum class stones
{
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame
};

// spawn resources
// inhabitants = bodiless + blurry + takes entire tile

// mian.cpp

int help(void);
