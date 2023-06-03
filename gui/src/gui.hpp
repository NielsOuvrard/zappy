/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#pragma once
#include "zappy_gui.hpp"

class Gui
{
public:
    Gui(std::string data);
    ~Gui();
    void run(void);

private:
    void draw_map(void);

    int _size_x;
    int _size_y;
    int _freq;
};
