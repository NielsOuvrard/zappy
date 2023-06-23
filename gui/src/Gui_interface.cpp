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
    _window->setView(*_view_interface);
    // * BACKGROUND
    _sprites[ID_BACKGROUND].setPosition(-150, -180);
    _sprites[ID_BACKGROUND].setColor(sf::Color(255, 255, 255, 255 * 0.8));
    _sprites[ID_BACKGROUND].setTexture(_textures[ID_BACKGROUND]);
    _sprites[ID_BACKGROUND].setScale(1.2, 1.5);
    _window->draw(_sprites[ID_BACKGROUND]);

    sf::Vector2u in_sprite_sheet[7] = {
        {0, 0},  // food
        {1, 0},  // linemate
        {1, 1},  // deraumere
        {1, 3},  // sibur
        {1, 2},  // mendiane
        {12, 5}, // phiras
        {2, 4}   // thystame
    };

    _text.setFillColor(sf::Color::Black);

    // * FOOD
    _sprites[ID_FOOD].setPosition(10, 10);
    _textures[ID_FOOD].setSmooth(false);
    _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
    _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
    _sprites[ID_FOOD].setScale(1, 1);
    _window->draw(_sprites[ID_FOOD]);

    _text.setString(_ressources[0]);
    _text.setPosition(70, 0);
    _window->draw(_text);

    // * STONES
    for (size_t i = 1; i < 7; i++)
    {
        _sprites[ID_STONE].setPosition(0, i * 50);
        _sprites[ID_STONE].setTextureRect(sf::IntRect(in_sprite_sheet[i].x * SIZE_STONE, in_sprite_sheet[i].y * SIZE_STONE, SIZE_STONE, SIZE_STONE));
        _sprites[ID_STONE].setScale(0.1, 0.1);
        _window->draw(_sprites[ID_STONE]);

        _text.setString(_ressources[i]);
        _text.setPosition(70, i * 50);
        _window->draw(_text);
    }

    int eggs = 0;
    for (size_t i = 0; i < _eggs.size(); i++)
        if (_eggs[i].y == _selected_tile_y && _eggs[i].x == _selected_tile_x)
            eggs++;

    _sprites[ID_EGG].setPosition(0, 350);
    _textures[ID_EGG].setSmooth(false);
    _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
    _sprites[ID_EGG].setScale(0.75, 0.75);
    _window->draw(_sprites[ID_EGG]);

    _text.setString("eggs : " + std::to_string(eggs));
    _text.setPosition(70, 350);
    _window->draw(_text);

    for (size_t i = 0; i < 7; i++)
    {
        _text.setString("x" + std::to_string(_map[_selected_tile_y][_selected_tile_x].ressources[i]));
        _text.setPosition(250, i * 50);
        _window->draw(_text);
    }

    _text.setString("x = " + std::to_string(_selected_tile_x));
    _text.setPosition(0, 450);
    _window->draw(_text);

    _text.setString("y = " + std::to_string(_selected_tile_y));
    _text.setPosition(0, 500);
    _window->draw(_text);

    int players = 0;
    for (size_t i = 0; i < _players.size(); i++)
        if (_players[i].y == _selected_tile_y && _players[i].x == _selected_tile_x)
            players++;
    _text.setString("Player : " + std::to_string(players));
    _text.setPosition(0, 550);
    _window->draw(_text);

    _text.setString("Frequency: " + std::to_string(10 * _slider_value));
    _text.setPosition(0, 600);
    _window->draw(_text);

    _slider.setFillColor(sf::Color(180, 255, 180));
    _slider.setSize(sf::Vector2f(200, 20));
    _slider.setPosition(50, 650);
    _window->draw(_slider);

    _slider.setFillColor(sf::Color(0, 200, 0));
    _slider.setSize(sf::Vector2f(2 * _slider_value, 20));
    _window->draw(_slider);

    sf::CircleShape cursor(16);
    cursor.setPosition(50 + 2 * _slider_value - 16, 650 - 16 / 2);
    cursor.setFillColor(sf::Color(0, 230, 0));
    _window->draw(cursor);
}
