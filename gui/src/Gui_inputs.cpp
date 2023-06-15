/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define SPEED_MAX_X 50
#define SPEED_MAX_Y 20

void Gui::move_map(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
            _move_right = true;
        if (event.key.code == sf::Keyboard::Left)
            _move_left = true;
        if (event.key.code == sf::Keyboard::Down)
            _move_down = true;
        if (event.key.code == sf::Keyboard::Up)
            _move_up = true;
        // std::cout << _view_main->getCenter().x << std::endl;
        // std::cout << _view_main->getCenter().y << std::endl;
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Right)
            _move_right = false;
        if (event.key.code == sf::Keyboard::Left)
            _move_left = false;
        if (event.key.code == sf::Keyboard::Down)
            _move_down = false;
        if (event.key.code == sf::Keyboard::Up)
            _move_up = false;
    }

    // * BOOLEAN MOVEMENTS
    if (_move_right && _speed_x >= -1)
    {
        _speed_x += 1;
        _speed_x *= 1.1;
        if (_speed_x >= SPEED_MAX_X)
            _speed_x = SPEED_MAX_X;
    }
    else if (_move_left && _speed_x <= 1)
    {
        _speed_x -= 1;
        _speed_x *= 1.1;
        if (_speed_x <= -SPEED_MAX_X)
            _speed_x = -SPEED_MAX_X;
    }
    if (_move_down && _speed_y >= -1)
    {
        _speed_y += 1;
        _speed_y *= 1.1;
        if (_speed_y >= SPEED_MAX_Y)
            _speed_y = SPEED_MAX_Y;
    }
    else if (_move_up && _speed_y <= 1)
    {
        _speed_y -= 1;
        _speed_y *= 1.1;
        if (_speed_y <= -SPEED_MAX_Y)
            _speed_y = -SPEED_MAX_Y;
    }
    _speed_x *= 0.95;
    _speed_y *= 0.95;

    _view_main->move(_speed_x, _speed_y);
    // _pos = _view_main->getCenter();
}
