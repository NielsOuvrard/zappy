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
// differents players by nivel
// frequency move GUI side

// incantation
// broadcast

// void Gui::incantation

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

#define INTERFACE_HIDE -500
#define INTERFACE_SHOW 0

void Gui::run(void)
{
    sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
    _window = &win;

    sf::View view(sf::FloatRect(0, 0, 1920, 1080));
    view.setCenter(sf::Vector2f(SIZE_TILE * (DECOR_SIZE + _size_y + DECOR_SIZE), 0));
    view.zoom(_zoom);
    _view_main = &view;

    sf::View view_2(sf::FloatRect(0, 0, 1920, 1080));
    _view_interface = &view_2;

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
                if (event.key.code == sf::Keyboard::P && _zoom < ZOOM_MAX)
                {
                    _zoom += 0.1;
                    // _view_main->getSize();
                    std::cout << _view_main->getSize().x << _view_main->getSize().y << std::endl;
                    _view_main->getTransform();
                    std::cout << _view_main->getTransform().transformPoint(0, 0).x << _view_main->getTransform().transformPoint(0, 0).y << std::endl;
                    _view_main->getViewport();
                    std::cout << _view_main->getViewport().width << _view_main->getViewport().height << std::endl;
                    _view_main->zoom(0.9f);
                }
                if (event.key.code == sf::Keyboard::M && _zoom > ZOOM_MIN)
                {
                    _zoom -= 0.1;
                    _view_main->zoom(1.1f);
                }
                if (event.key.code == sf::Keyboard::O)
                {
                    _view_interface->zoom(0.9f);
                }
                if (event.key.code == sf::Keyboard::L)
                {
                    _view_interface->zoom(1.1f);
                }
                if (event.key.code == sf::Keyboard::I)
                {
                    _interface_show = !_interface_show;
                }
                move_tile(event);
            }
        }
        if (_interface_show && _interface_center_value < INTERFACE_SHOW)
        {
            _interface_center_value += 10;
            _view_interface->setCenter(0, 0);
        }
        else if (!_interface_show && _interface_center_value > INTERFACE_HIDE)
        {
            _interface_center_value -= 10;
            _view_interface->setCenter(_interface_center_value, 0);
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