/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define SPEED_MAX 15

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
    if (_move_right)
    {
        _speed_x *= 1.1;
        _speed_x += 1;
        if (_speed_x >= SPEED_MAX)
            _speed_x = SPEED_MAX;
    }
    if (_move_left)
    {
        _speed_x *= 1.1;
        _speed_x -= 1;
        if (_speed_x <= -SPEED_MAX)
            _speed_x = -SPEED_MAX;
    }
    if (_move_up)
    {
        _speed_y *= 1.1;
        _speed_y -= 1;
        if (_speed_y <= -SPEED_MAX)
            _speed_y = -SPEED_MAX;
    }
    if (_move_down)
    {
        _speed_y *= 1.1;
        _speed_y += 1;
        if (_speed_y >= SPEED_MAX)
            _speed_y = SPEED_MAX;
    }

    if (_speed_x > 0 && !_move_right)
    {
        _speed_x *= 0.95;
        if (_speed_x < 1)
            _speed_x = 0;
    }
    if (_speed_x < 0 && !_move_left)
    {
        _speed_x *= 0.95;
        if (_speed_x > -1)
            _speed_x = 0;
    }
    if (_speed_y > 0 && !_move_down)
    {
        _speed_y *= 0.95;
        if (_speed_y < 1)
            _speed_y = 0;
    }
    if (_speed_y < 0 && !_move_up)
    {
        _speed_y *= 0.95;
        if (_speed_y > -1)
            _speed_y = 0;
    }
    _shift_x -= _speed_x;
    _shift_y += _speed_y;
}
