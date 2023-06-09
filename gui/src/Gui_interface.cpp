/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

void Gui::interface(void)
{
    for (int i = 0; i < 7; i++)
    {
        _text.setString(_ressources[i]);
        _text.setPosition(0, i * 50);
        _window->draw(_text);
    }

    int stones[7] = {_map[_selected_tile_y][_selected_tile_x].food, _map[_selected_tile_y][_selected_tile_x].linemate, _map[_selected_tile_y][_selected_tile_x].deraumere, _map[_selected_tile_y][_selected_tile_x].sibur, _map[_selected_tile_y][_selected_tile_x].mendiane, _map[_selected_tile_y][_selected_tile_x].phiras, _map[_selected_tile_y][_selected_tile_x].thystame};

    for (int i = 0; i < 7; i++)
    {
        _text.setString("x" + std::to_string(stones[i]));
        _text.setPosition(200, i * 50);
        _window->draw(_text);
    }

    _text.setString("x = " + std::to_string(_selected_tile_x));
    _text.setPosition(0, 400);
    _window->draw(_text);

    _text.setString("y = " + std::to_string(_selected_tile_y));
    _text.setPosition(0, 450);
    _window->draw(_text);
}
