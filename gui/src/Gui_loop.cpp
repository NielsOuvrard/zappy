/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define MAX_HEIGHT 32

void Gui::run(void)
{
    sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
    _window = &win;
    load_map();
    load_textures();
    // perlin_noise();

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    _window->setFramerateLimit(60);
    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                _window->setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    _zoom *= 1.1;
                    _shift_x *= 1.1;
                    _shift_y *= 1.1;
                }
                if (event.key.code == sf::Keyboard::M)
                {
                    _zoom /= 1.1;
                    _shift_x /= 1.1;
                    _shift_y /= 1.1;
                }
                if (event.key.code == sf::Keyboard::Z)
                {
                    if (_selected_tile_y > 0)
                        _selected_tile_y -= 1;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    if (_selected_tile_y < _size_y - 1)
                        _selected_tile_y += 1;
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    if (_selected_tile_x > 0)
                        _selected_tile_x -= 1;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    if (_selected_tile_x < _size_x - 1)
                        _selected_tile_x += 1;
                }
            }
        }
        move_map(event);
        _window->clear();
        // draw_map(_window);
        draw_decor_map();
        interface();

        if (_up_selected_tile)
            _height_selected_tile += 1;
        else
            _height_selected_tile -= 1;
        if (_height_selected_tile > MAX_HEIGHT)
        {
            _height_selected_tile = MAX_HEIGHT;
            _up_selected_tile = false;
        }
        else if (_height_selected_tile < 0)
        {
            _height_selected_tile = 0;
            _up_selected_tile = true;
        }

        // _window->draw(shape);
        _window->display();
    }
    return;
}
