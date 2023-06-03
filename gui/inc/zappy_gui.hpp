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
#include <cstring>
#include <iostream>
#include <fstream>

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

// spawn resources
// inhabitants = bodiless + blurry + takes entire tile

// mian.cpp

int help(void);
