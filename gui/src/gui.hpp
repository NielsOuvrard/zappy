/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#pragma once
#include "zappy_gui.hpp"

typedef struct s_tile
{
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} t_tile;

class Gui
{
public:
    Gui(std::string data);
    ~Gui();
    void run(void);

private:
    void draw_map(sf::RenderWindow &window);
    void load_textures(void);

    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Texture> _textures;

    t_tile **_map;
    int _size_x;
    int _size_y;
    int _freq;
};
