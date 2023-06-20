/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define MAX_HEIGHT 32
#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

// * Mandatory
// broadcast
// modify interface size ?
// not connected to server
// disp player inventory
// disp nmb player by team
// disp nmb player by tile
// selection player

// * Optional
// water animation ?
// smooth zoom
// move according to zoom

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

#define INTERFACE_HIDE 430
#define INTERFACE_SHOW 0

void Gui::event_slider(sf::Event event)
{
    _slider.setSize(sf::Vector2f(200, 20));
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
            if (_slider.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
            {
                _slider_selected = true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            _slider_selected = false;
            _network->send_data("sst " + std::to_string(_slider_value * 10) + "\n");
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (_slider_selected)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
            _slider_value = (mousePosition.x - _slider.getPosition().x) / 2;
            if (_slider_value < 1)
                _slider_value = 1;
            else if (_slider_value > 100)
                _slider_value = 100;
        }
    }
}

void Gui::run(void)
{
    sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "Zappy");
    _window = &win;

    _slider = sf::RectangleShape(sf::Vector2f(200, 20));

    sf::View view(sf::FloatRect(0, 0, 1920, 1080));
    view.setCenter(sf::Vector2f(SIZE_TILE * (DECOR_SIZE + _size_y + DECOR_SIZE), 0));
    view.zoom(_zoom);
    _view_main = &view;

    sf::View view_2(sf::FloatRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT));
    _view_interface = &view_2;

    load_map();
    load_textures();
    // create_outdoor_map();
    // perlin_noise();
    // clock
    sf::Clock clock;
    sf::Clock clock_particules;
    sf::Time time;
    _window->setView(*_view_main);
    _view_height = _view_main->getSize().y;
    _view_width = _view_main->getSize().x;

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
            // * RESIZE
            if (event.type == sf::Event::Resized)
            {
                sf::Vector2f pos = _view_main->getCenter();
                sf::FloatRect visibleArea(pos.x - event.size.width / 2, pos.y - event.size.height / 2, event.size.width, event.size.height);
                _view_main->reset(visibleArea);

                sf::FloatRect visibleAreaInterface(0, 0, event.size.width, event.size.height);
                _view_interface->reset(visibleAreaInterface);
            }
            // * ZOOM
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P && _zoom < ZOOM_MAX)
                {
                    _zoom += 0.1;
                    _view_main->setSize(_view_width * _zoom, _view_height * _zoom);
                }
                if (event.key.code == sf::Keyboard::M && _zoom > ZOOM_MIN)
                {
                    _zoom -= 0.1;
                    _view_main->setSize(_view_width * _zoom, _view_height * _zoom);
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
            event_slider(event);
        }
        // * INTERFACE
        if (_interface_show && _interface_center_value > INTERFACE_SHOW)
        {
            _interface_center_value -= 10;
            _view_interface->setCenter(DISPLAY_WIDTH / 2 + _interface_center_value, DISPLAY_HEIGHT / 2);
        }
        else if (!_interface_show && _interface_center_value < INTERFACE_HIDE)
        {
            _interface_center_value += 10;
            _view_interface->setCenter(DISPLAY_WIDTH / 2 + _interface_center_value, DISPLAY_HEIGHT / 2);
        }
        move_map(event);
        draw_map();
        draw_particles();
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

        if (clock_particules.getElapsedTime().asMilliseconds() > 100)
        {
            // add particles
            for (size_t i = 0; i < _size_y; i++)
            {
                for (size_t j = 0; j < _size_x; j++)
                {
                    if (_map[i][j].is_incanting)
                    {
                        std::cout << "incanting in " << i << " " << j << std::endl;
                        sf::Color color_according_to_level[8] = {
                            sf::Color(255, 255, 255, 140),
                            sf::Color(255, 255, 0, 140),
                            sf::Color(255, 0, 0, 140),
                            sf::Color(0, 255, 0, 140),
                            sf::Color(0, 0, 255, 140),
                            sf::Color(255, 0, 255, 140),
                            sf::Color(0, 255, 255, 140),
                            sf::Color(10, 10, 10, 140),
                        };
                        // (j * 64 + i * 64 + 32),
                        // (i * 32 - j * 32 + 16 - height));
                        std::cout << "pos x " << ((DECOR_SIZE + j) * 64) + ((DECOR_SIZE + i) * 64) + 42 << std::endl;
                        std::cout << "pos y " << (int)((int)(DECOR_SIZE + i) * 32) - (int)((int)(DECOR_SIZE + j) * 32) + 16 << std::endl;
                        _particles.push_back((s_particle){
                            sf::Vector2f(
                                ((DECOR_SIZE + j) * 64) + ((DECOR_SIZE + i) * 64) + 42,
                                (int)((int)(DECOR_SIZE + i) * 32) - (int)((int)(DECOR_SIZE + j) * 32) + 16),
                            color_according_to_level[_map[i][j].is_incanting], 15});
                        // (sf::Vector2f(_map[i][j].x, _map[i][j].y), sf::Vector2f(0, -1), sf::Color::Yellow));
                    }
                }
            }
            for (size_t i = 0; i < _particles.size(); i++)
            {
                _particles[i].lifetime -= 1;
                int rand_y = rand() % 14;
                int rand_x = rand() % 14;
                _particles[i].pos.y += 2 - rand_y;
                _particles[i].pos.x += 7 - rand_x;

                if (_particles[i].lifetime <= 0)
                {
                    _particles.erase(_particles.begin() + i);
                }
            }
            clock_particules.restart();
        }

        if (clock.getElapsedTime().asMilliseconds() > 1000)
        {
            _waves++;
            clock.restart();
        }
    }
    return;
}
