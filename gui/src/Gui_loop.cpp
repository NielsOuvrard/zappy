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
// broadcast (Missing sprite but working)
// modify interface size ?
// // not connected to server
// // disp player inventory
// // disp nmb player by team
// // disp nmb player by tile
// an arrow on selected player

// * Optional
// water animation ?
// // smooth zoom
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

void Gui::handle_clocks(sf::Clock *clock, sf::Clock *clock_particules)
{
    if (clock_particules->getElapsedTime().asMilliseconds() > 100)
    {
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
        // add particles
        for (int i = 0; i < _size_y; i++)
        {
            for (int j = 0; j < _size_x; j++)
            {
                if (_map[i][j].is_incanting)
                {
                    _particles.push_back((s_particle){
                        sf::Vector2f(
                            ((DECOR_SIZE + j) * 64) + ((DECOR_SIZE + i) * 64) + 42,
                            ((DECOR_SIZE + i) * 32) - ((DECOR_SIZE + j) * 32) + 16),
                        color_according_to_level[_map[i][j].is_incanting], 15, j, i});
                }
                _map[i][j].is_incanting = 0;
                for (int k = 0; (size_t)k < _players.size(); k++)
                {
                    if (_players[k].x == j && _players[k].y == i && _players[k].is_incanting)
                    {
                        _map[i][j].is_incanting = _players[k].level;
                    }
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

        // add player particles
        if (_players.size() > 0)
        {
            if ((size_t)_selected_player < _players.size() && _players[_selected_player].is_incanting) {
                int x = 185;
                int y = 130;
                _player_particles.push_back((s_particle){
                    sf::Vector2f(x, y),
                    color_according_to_level[_players[_selected_player].level], 15, x, y});
            }
            for (size_t i = 0; i < _player_particles.size(); i++)
            {
                _player_particles[i].lifetime -= 1;
                int rand_y = rand() % 14;
                int rand_x = rand() % 14;
                _player_particles[i].pos.y += 2 - rand_y;
                _player_particles[i].pos.x += 7 - rand_x;

                if (_player_particles[i].lifetime <= 0)
                {
                    _player_particles.erase(_player_particles.begin() + i);
                }
            }
        }
        clock_particules->restart();
    }

    if (clock->getElapsedTime().asMilliseconds() > 1000)
    {
        for (int i = 0; (size_t)i < _players.size(); i++)
            if (_players[i].broadcast_time > 0)
                _players[i].broadcast_time -= 1;
        if (_messages.size() > 0)
            _messages_cooldown--;
        if (_messages.size() > 0 && _messages_cooldown <= 0) {
            _messages.erase(_messages.begin());
            _messages_cooldown = 5;
        }
        _waves++;
        clock->restart();
    }
}

void Gui::event_slider(sf::Event event)
{
    _slider.setSize(sf::Vector2f(200 * _window->getSize().x / 1920, 20 * _window->getSize().y / 1080));
    _slider.setPosition(50 * _window->getSize().x / 1920, 650 * _window->getSize().y / 1080);
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
            _slider_value = (float)(mousePosition.x - _slider.getPosition().x) / (float)_slider.getSize().x * 100.0;
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

    sf::View view_3(sf::FloatRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT));
    view_3.setCenter(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, DISPLAY_HEIGHT / 2);
    _view_player = &view_3;

    load_map();
    load_textures();
    // create_outdoor_map();
    // perlin_noise();
    // clock
    sf::Clock clock;
    sf::Clock clock_particules;
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
                _view_main->setSize(_view_width * _actual_zoom, _view_height * _actual_zoom);

                // sf::FloatRect visibleAreaInterface(0, 0, event.size.width, event.size.height);
                // _view_interface->reset(visibleAreaInterface);
            }
            // * ZOOM
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P && _zoom < ZOOM_MAX)
                {
                    _zoom += 0.1;
                }
                if (event.key.code == sf::Keyboard::M && _zoom > ZOOM_MIN)
                {
                    _zoom -= 0.1;
                }
                if (event.key.code == sf::Keyboard::O)
                {
                    // _view_interface->zoom(0.9f);
                }
                if (event.key.code == sf::Keyboard::L)
                {
                    // _view_interface->zoom(1.1f);
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    if (_selected_player + 1 < _players.size())
                        _selected_player++;
                    else
                        _selected_player = 0;
                    if (_players.size() > 0)
                        _network->send_data("pin " + std::to_string(_players[_selected_player].id) + "\n");
                    // pos
                    // _network->send_data("ppo " + std::to_string(_players[_selected_player].id) + "\n");
                }
                if (event.key.code == sf::Keyboard::E)
                {
                    if (_selected_player > 0)
                        _selected_player--;
                    else
                        _selected_player = _players.size() - 1;
                    if (_players.size() > 0)
                        _network->send_data("pin " + std::to_string(_players[_selected_player].id) + "\n");
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
            // -(DISPLAY_WIDTH / 2) + 280
            _interface_center_value -= 10;
            _view_interface->setCenter(DISPLAY_WIDTH / 2 + _interface_center_value, _view_interface->getCenter().y);
            _view_player->setCenter(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, _view_player->getCenter().y);
        }
        else if (!_interface_show && _interface_center_value < INTERFACE_HIDE)
        {
            _interface_center_value += 10;
            _view_interface->setCenter(DISPLAY_WIDTH / 2 + _interface_center_value, _view_interface->getCenter().y);
            _view_player->setCenter(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, _view_player->getCenter().y);
        }
        // * SMOOTH ZOOM
        if (_zoom - _actual_zoom > 0.01)
        {
            _actual_zoom += 0.01;
            _view_main->setSize(_view_width * _actual_zoom, _view_height * _actual_zoom);
        }
        else if (_zoom - _actual_zoom < -0.01)
        {
            _actual_zoom -= 0.01;
            _view_main->setSize(_view_width * _actual_zoom, _view_height * _actual_zoom);
        }
        // * DRAW
        move_map(event);
        draw_map();
        interface();
        player();

        if (_messages.size() > 0)
        {
            sf::Text serverMessagesText;
            serverMessagesText.setFont(_font);
            serverMessagesText.setString("Server message : " + _messages[0]);
            serverMessagesText.setCharacterSize(50);
            serverMessagesText.setFillColor(sf::Color::Blue);
            serverMessagesText.setStyle(sf::Text::Bold);
            serverMessagesText.setOrigin(serverMessagesText.getLocalBounds().width / 2, serverMessagesText.getLocalBounds().height / 2);
            serverMessagesText.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 30);

            sf::RectangleShape serverMessagesBackground(sf::Vector2f(
                serverMessagesText.getLocalBounds().width + 20,
                serverMessagesText.getLocalBounds().height + 20));

            serverMessagesBackground.setFillColor(sf::Color(0, 0, 0, 140));
            serverMessagesBackground.setOrigin(serverMessagesBackground.getLocalBounds().width / 2, serverMessagesBackground.getLocalBounds().height / 2);
            serverMessagesBackground.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 40);

            _window->draw(serverMessagesBackground);
            _window->draw(serverMessagesText);
        }
        if (*_server_stopped == true)
        {
            sf::Text serverDisconnectedText;
            serverDisconnectedText.setFont(_font);
            serverDisconnectedText.setString("Server disconnected");
            serverDisconnectedText.setCharacterSize(50);
            serverDisconnectedText.setFillColor(sf::Color::Red);
            serverDisconnectedText.setStyle(sf::Text::Bold);
            serverDisconnectedText.setOrigin(serverDisconnectedText.getLocalBounds().width / 2, serverDisconnectedText.getLocalBounds().height / 2);
            serverDisconnectedText.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 100);

            sf::RectangleShape serverDisconnectedBackground(sf::Vector2f(
                serverDisconnectedText.getLocalBounds().width + 20,
                serverDisconnectedText.getLocalBounds().height + 20));

            serverDisconnectedBackground.setFillColor(sf::Color(0, 0, 0, 140));
            serverDisconnectedBackground.setOrigin(serverDisconnectedBackground.getLocalBounds().width / 2, serverDisconnectedBackground.getLocalBounds().height / 2);
            serverDisconnectedBackground.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 110);

            _window->draw(serverDisconnectedBackground);
            _window->draw(serverDisconnectedText);
        }
        if (_game_over == true)
        {
            sf::Text gameOverText;
            gameOverText.setFont(_font);
            gameOverText.setString("Game Over! Winner: " + _winner);
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::Green);
            gameOverText.setStyle(sf::Text::Bold);
            gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
            gameOverText.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 170);

            sf::RectangleShape gameOverBackground(sf::Vector2f(
                gameOverText.getLocalBounds().width + 20,
                gameOverText.getLocalBounds().height + 20));

            gameOverBackground.setFillColor(sf::Color(0, 0, 0, 140));
            gameOverBackground.setOrigin(gameOverBackground.getLocalBounds().width / 2, gameOverBackground.getLocalBounds().height / 2);
            gameOverBackground.setPosition(-(DISPLAY_WIDTH / 2) + 280 - _interface_center_value, 180);

            _window->draw(gameOverBackground);
            _window->draw(gameOverText);
        }

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
        handle_clocks(&clock, &clock_particules);
    }
    return;
}
