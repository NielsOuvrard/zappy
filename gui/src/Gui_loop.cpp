/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define MAX_HEIGHT 32

// modify interface size ?
// hide interface ?
// buffer for network ?
// water animation ?
// smooth zoom
// move according to zoom
// begin in the middle of the map
// differents players by nivel

void Gui::move_tile(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Z)
    {
        _selected_tile_y -= 1;
        if (_selected_tile_y < 0)
            _selected_tile_y = _size_y - 1;
    }
    if (event.key.code == sf::Keyboard::S)
    {
        _selected_tile_y += 1;
        if (_selected_tile_y > _size_y - 1)
            _selected_tile_y = 0;
    }
    if (event.key.code == sf::Keyboard::Q)
    {
        _selected_tile_x -= 1;
        if (_selected_tile_x < 0)
            _selected_tile_x = _size_x - 1;
    }
    if (event.key.code == sf::Keyboard::D)
    {
        _selected_tile_x += 1;
        if (_selected_tile_x > _size_x - 1)
            _selected_tile_x = 0;
    }
}

void Gui::run(void)
{
    sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
    _window = &win;

    sf::View view(sf::FloatRect(0, 0, 1920, 1080));
    view.setCenter(sf::Vector2f(DECOR_SIZE + _size_x / 2, DECOR_SIZE + _size_y / 2));
    _view_main = &view;

    sf::View view_2(sf::FloatRect(0, 0, 1920, 1080));
    _view_interface = &view_2;

    _view_main->setCenter(sf::Vector2f(DECOR_SIZE + _size_x / 2, DECOR_SIZE + _size_y / 2));

    load_map();
    load_textures();
    // create_outdoor_map();
    // perlin_noise();
    // clock
    sf::Clock clock;
    sf::Time time;
    _window->setView(*_view_main);

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    _window->setFramerateLimit(60);
    while (_window->isOpen())
    {
        _window->clear();
        _window->setView(*_view_main);

        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2f pos = _view_main->getCenter();
                sf::FloatRect visibleArea(pos.x - event.size.width / 2, pos.y - event.size.height / 2, event.size.width, event.size.height);
                _view_main->reset(visibleArea);

                sf::FloatRect visibleAreaInterface(0, 0, event.size.width, event.size.height);
                _view_interface->reset(visibleAreaInterface);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    _zoom += 0.1;
                    if (ZOOM_MAX < _zoom)
                        _zoom = ZOOM_MAX;
                    else
                        _view_main->zoom(0.9f);
                }
                if (event.key.code == sf::Keyboard::M)
                {
                    _zoom -= 0.1;
                    if (_zoom < ZOOM_MIN)
                        _zoom = ZOOM_MIN;
                    else
                        _view_main->zoom(1.1f);
                }
                move_tile(event);
            }
        }
        move_map(event);
        draw_map();
        interface();

        // * animation up and down
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

        if (clock.getElapsedTime().asMilliseconds() > 1000)
        {
            // sf::sleep(sf::milliseconds(1000 / 60 - clock.getElapsedTime().asMilliseconds()));
            _waves++;
            clock.restart();
        }
    }
    return;
}

// old move diagonal
// void Gui::move_tile(sf::Event event)
// {
//     if (event.key.code == sf::Keyboard::Z)
//     {
//         _selected_tile_y -= 1;
//         _selected_tile_x += 1;
//     }
//     if (event.key.code == sf::Keyboard::S)
//     {
//         _selected_tile_y += 1;
//         _selected_tile_x -= 1;
//     }
//     if (event.key.code == sf::Keyboard::Q)
//     {
//         _selected_tile_x -= 1;
//         _selected_tile_y -= 1;
//     }
//     if (event.key.code == sf::Keyboard::D)
//     {
//         _selected_tile_x += 1;
//         _selected_tile_y += 1;
//     }

//     //
//     if (_selected_tile_x > _size_x - 1)
//     {
//         _selected_tile_x = _selected_tile_x - _selected_tile_y;
//         _selected_tile_y = 0;
//     }
//     else if (_selected_tile_x < 0)
//     {
//         _selected_tile_y = _size_x - _selected_tile_x;
//         _selected_tile_x = _size_x - 1;
//     }
//     if (_selected_tile_y < 0)
//     {
//         _selected_tile_x = _size_y - _selected_tile_y;
//         _selected_tile_y = _size_y - 1;
//     }
//     else if (_selected_tile_y > _size_y - 1)
//     {
//         _selected_tile_y = _selected_tile_y - _selected_tile_x;
//         _selected_tile_x = 0;
//     }
// }