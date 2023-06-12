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

    sf::RectangleShape shape(sf::Vector2f(250, 550));
    // opacity = 0.5;
    shape.setFillColor(sf::Color(0, 0, 0, 128));
    shape.setPosition(0, 0);
    _window->draw(shape);

    for (size_t i = 0; i < 7; i++)
    {
        _text.setString(_ressources[i]);
        _text.setPosition(0, i * 50);
        _window->draw(_text);
    }

    int eggs = 0;
    for (size_t i = 0; i < _eggs.size(); i++)
        if (_eggs[i].y == _selected_tile_y && _eggs[i].x == _selected_tile_x)
            eggs++;

    _text.setString("eggs : " + std::to_string(eggs));
    _text.setPosition(0, 350);
    _window->draw(_text);

    for (size_t i = 0; i < 7; i++)
    {
        _text.setString("x" + std::to_string(_map[_selected_tile_y][_selected_tile_x].ressources[i]));
        _text.setPosition(200, i * 50);
        _window->draw(_text);
    }

    _text.setString("x = " + std::to_string(_selected_tile_x));
    _text.setPosition(0, 450);
    _window->draw(_text);

    _text.setString("y = " + std::to_string(_selected_tile_y));
    _text.setPosition(0, 500);
    _window->draw(_text);
}
