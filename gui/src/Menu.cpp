/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(std::string ip, std::string port)
{
    _ip = ip;
    _port = port;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
    _button_init_size = sf::Vector2f(1.0f, 1.0f);

    sf::Texture background_texture;
    if (!background_texture.loadFromFile("gui/assets/menu.png"))
        exit(84);
    _background_texture = background_texture;
    _background.setTexture(background_texture);

    if (!_help_texture.loadFromFile("gui/assets/Help_Menu.png"))
        exit(84);

    _help_menu.setTexture(_help_texture);
    _help_menu.setPosition(40000, 10000);

    if (!_adumu.loadFromFile("gui/assets/adumu.ttf"))
        exit(84);
    _title.setFont(_adumu);
    _title.setString("ZAPPY");
    _title.setCharacterSize(128);
    _title.setFillColor(sf::Color::White);
    _title.setOutlineColor(sf::Color::Black);
    _title.setOutlineThickness(2);
    _title.setPosition((_window->getSize().x / 2) - (_title.getGlobalBounds().width / 2), 0);

    _input_host.setFont(_adumu);
    _input_host.setCharacterSize(24);
    _input_host.setFillColor(sf::Color::White);
    _input_host.setOutlineColor(sf::Color::Black);
    _input_host.setOutlineThickness(2);
    _input_host.setOrigin(_input_host.getGlobalBounds().width / 2, _input_host.getGlobalBounds().height / 2);
    _input_host.setPosition(40000, 40000);
    _input_host.setString(_ip);

    _input_port.setFont(_adumu);
    _input_port.setCharacterSize(24);
    _input_port.setFillColor(sf::Color::White);
    _input_port.setOutlineColor(sf::Color::Black);
    _input_port.setOutlineThickness(2);
    _input_port.setOrigin(_input_port.getGlobalBounds().width / 2, _input_port.getGlobalBounds().height / 2);
    _input_port.setPosition(40000, 40000);
    _input_port.setString(_port);

    _ip_text.setFont(_adumu);
    _ip_text.setCharacterSize(40);
    _ip_text.setFillColor(sf::Color::White);
    _ip_text.setOutlineColor(sf::Color::Black);
    _ip_text.setOutlineThickness(2);
    _ip_text.setOrigin(_ip_text.getGlobalBounds().width / 2, _ip_text.getGlobalBounds().height / 2);
    _ip_text.setPosition(40000, 40000);
    _ip_text.setString("Host");

    _port_text.setFont(_adumu);
    _port_text.setCharacterSize(40);
    _port_text.setFillColor(sf::Color::White);
    _port_text.setOutlineColor(sf::Color::Black);
    _port_text.setOutlineThickness(2);
    _port_text.setOrigin(_port_text.getGlobalBounds().width / 2, _port_text.getGlobalBounds().height / 2);
    _port_text.setPosition(40000, 40000);
    _port_text.setString("Port");

    sf::Texture start_texture;
    if (!start_texture.loadFromFile("gui/assets/start_button.png"))
        exit(84);
    _buttons_textures.push_back(start_texture);
    sf::Sprite start_sprite;
    start_sprite.setTexture(start_texture);
    start_sprite.setOrigin(start_sprite.getGlobalBounds().width / 2, start_sprite.getGlobalBounds().height / 2);
    start_sprite.setPosition(_window->getSize().x / 2, _window->getSize().y / 2);
    _buttons_sprites.push_back(start_sprite);
    _buttons_pressed.push_back(false);
    _buttons_tags.push_back("start");

    sf::Texture help_texture;
    if (!help_texture.loadFromFile("gui/assets/help_button.png"))
        exit(84);
    _buttons_textures.push_back(help_texture);
    sf::Sprite help_sprite;
    help_sprite.setTexture(help_texture);
    help_sprite.setOrigin(help_sprite.getGlobalBounds().width / 2, help_sprite.getGlobalBounds().height / 2);
    help_sprite.setPosition(_window->getSize().x / 2, _window->getSize().y / 2 + 100);
    _buttons_sprites.push_back(help_sprite);
    _buttons_pressed.push_back(false);
    _buttons_tags.push_back("help");

    sf::Texture quit_texture;
    if (!quit_texture.loadFromFile("gui/assets/quit_button.png"))
        exit(84);
    _buttons_textures.push_back(quit_texture);
    sf::Sprite quit_sprite;
    quit_sprite.setTexture(quit_texture);
    quit_sprite.setOrigin(quit_sprite.getGlobalBounds().width / 2, quit_sprite.getGlobalBounds().height / 2);
    quit_sprite.setPosition(_window->getSize().x / 2, _window->getSize().y / 2 + 200);
    _buttons_sprites.push_back(quit_sprite);
    _buttons_pressed.push_back(false);
    _buttons_tags.push_back("quit");

    _param = false;

    _buttons_textures.push_back(start_texture);
    sf::Sprite start_sprite2;
    start_sprite2.setTexture(start_texture);
    start_sprite2.setPosition(40000, 40000);
    _buttons_sprites.push_back(start_sprite2);
    _buttons_pressed.push_back(false);
    _buttons_tags.push_back("start2");

    _input_host_rect.setSize(sf::Vector2f(300, 75));
    _input_host_rect.setFillColor(sf::Color(0, 0, 0, 100));
    _input_host_rect.setOutlineColor(sf::Color::Black);
    _input_host_rect.setOutlineThickness(2);
    _input_host_rect.setPosition(40000, 40000);

    _input_port_rect.setSize(sf::Vector2f(300, 75));
    _input_port_rect.setFillColor(sf::Color(0, 0, 0, 100));
    _input_port_rect.setOutlineColor(sf::Color::Black);
    _input_port_rect.setOutlineThickness(2);
    _input_port_rect.setPosition(40000, 40000);
}

Menu::~Menu()
{
}

void Menu::menu_draw(void)
{
    _window->clear();
    _background.setTexture(_background_texture);
    // resize background according to window size
    _window->draw(_background);
    _window->draw(_title);
    for (int i = 0; (size_t)i < _buttons_sprites.size(); i++) {
        _buttons_sprites[i].setTexture(_buttons_textures[i]);
        _window->draw(_buttons_sprites[i]);
    }
    _window->draw(_help_menu);
    _window->draw(_input_host_rect);
    _window->draw(_input_port_rect);
    _window->draw(_input_host);
    _window->draw(_input_port);
    _window->draw(_ip_text);
    _window->draw(_port_text);
}

void Menu::buttons_handling(sf::Event event)
{
    // Check if the mouse is over any button sprite
    sf::Vector2f mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    for (std::size_t i = 0; i < _buttons_sprites.size(); ++i)
    {
        if (_buttons_sprites[i].getGlobalBounds().contains(mousePosition) && !_buttons_pressed[i])
            // Scale the button sprite when the mouse is over it
            _buttons_sprites[i].setScale(_button_init_size + sf::Vector2f(0.1f, 0.1f));
        else if (!_buttons_pressed[i])
            // Reset the scale of the button sprite when the mouse is not over it
            _buttons_sprites[i].setScale(_button_init_size);
    }
    if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed) {
        mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        for (std::size_t i = 0; i < _buttons_sprites.size(); ++i)
        {
            if (_buttons_sprites[i].getGlobalBounds().contains(mousePosition)) {
                _buttons_sprites[i].setScale(_button_init_size - sf::Vector2f(0.1f, 0.1f));
                _buttons_pressed[i] = true;
            }
        }
    }
    if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
        mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        for (std::size_t i = 0; i < _buttons_sprites.size(); ++i)
        {
            if (_buttons_sprites[i].getGlobalBounds().contains(mousePosition)) {
                _buttons_sprites[i].setScale(_button_init_size + sf::Vector2f(0.1f, 0.1f));
                _buttons_pressed[i] = false;
                if (_buttons_tags[i] == "start") {
                    _param = true;
                }
                else if (_buttons_tags[i] == "help") {
                    _help_menu.setPosition(_window->getSize().x / 2 - _help_menu.getGlobalBounds().width / 2, _window->getSize().y / 2 - _help_menu.getGlobalBounds().height / 2);
                }
                else if (_buttons_tags[i] == "quit") {
                    _window->close();
                    exit(0);
                }
                else if (_buttons_tags[i] == "start2") {
                    _window->close();
                    return;
                }
            }
            else
                _buttons_sprites[i].setScale(_button_init_size);
        }
    }
    if (event.mouseButton.button == sf::Mouse::Left && _input_host_rect.getGlobalBounds().contains(mousePosition))
        _input_host_selected = true;
    else if (event.mouseButton.button == sf::Mouse::Left && !_input_host_rect.getGlobalBounds().contains(mousePosition))
        _input_host_selected = false;
    if (event.mouseButton.button == sf::Mouse::Left && _input_port_rect.getGlobalBounds().contains(mousePosition))
        _input_port_selected = true;
    else if (event.mouseButton.button == sf::Mouse::Left && !_input_port_rect.getGlobalBounds().contains(mousePosition))
        _input_port_selected = false;
    if (event.type == sf::Event::TextEntered && _input_host.getPosition().x != -40000 && _input_host.getPosition().y != -40000) {
        if (event.text.unicode < 128 && event.text.unicode != 8 && _input_host.getString().getSize() < 15 && _input_host_selected
        && ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == 46)) {
            _input_host.setString(_input_host.getString() + static_cast<char>(event.text.unicode));
        }
        else if (event.text.unicode == 8 && _input_host.getString().getSize() > 0 && _input_host_selected) {
            _input_host.setString(_input_host.getString().substring(0, _input_host.getString().getSize() - 1));
        }
    }
    if (event.type == sf::Event::TextEntered && _input_port.getPosition().x != -40000 && _input_port.getPosition().y != -40000) {
        if (event.text.unicode < 128 && event.text.unicode != 8 && _input_port.getString().getSize() < 5 && _input_port_selected && event.text.unicode >= 48 && event.text.unicode <= 57) {
            _input_port.setString(_input_port.getString() + static_cast<char>(event.text.unicode));
        }
        else if (event.text.unicode == 8 && _input_port.getString().getSize() > 0 && _input_port_selected) {
            _input_port.setString(_input_port.getString().substring(0, _input_port.getString().getSize() - 1));
        }
    }
    if (event.key.code == sf::Keyboard::Escape && _help_menu.getPosition().x != 40000)
        _help_menu.setPosition(40000, 10000);
    if (event.key.code == sf::Keyboard::Escape && _param)
        _param = false;
    if (_param) {
        _input_host_rect.setPosition(_window->getSize().x / 2 - _input_host_rect.getGlobalBounds().width / 2, _window->getSize().y / 2 - _input_host_rect.getGlobalBounds().height);
        _input_host.setPosition(_window->getSize().x / 2 - _input_host.getGlobalBounds().width / 2, _window->getSize().y / 2 - _input_host_rect.getGlobalBounds().height + _input_host_rect.getGlobalBounds().height / 2 - _input_host.getGlobalBounds().height / 2);
        _ip_text.setPosition(_window->getSize().x / 2 - _ip_text.getGlobalBounds().width / 2, _input_host_rect.getPosition().y - (_input_host_rect.getGlobalBounds().height / 3));
        _input_port_rect.setPosition(_window->getSize().x / 2 - _input_port_rect.getGlobalBounds().width / 2, _window->getSize().y / 2 + _input_port_rect.getGlobalBounds().height);
        _input_port.setPosition(_window->getSize().x / 2 - _input_port.getGlobalBounds().width / 2, _window->getSize().y / 2 + _input_port_rect.getGlobalBounds().height + _input_port_rect.getGlobalBounds().height / 2 - _input_port.getGlobalBounds().height / 2);
        _port_text.setPosition(_window->getSize().x / 2 - _port_text.getGlobalBounds().width / 2, _input_port_rect.getPosition().y - (_input_port_rect.getGlobalBounds().height / 3));
        for (int i = 0; (size_t)i < _buttons_sprites.size(); i++) {
            _buttons_sprites[i].setPosition(40000, 10000);
            if (_buttons_tags[i] == "start2")
                _buttons_sprites[i].setPosition(_input_port_rect.getPosition().x + _input_port_rect.getGlobalBounds().width / 2 - _buttons_sprites[i].getGlobalBounds().width / 2, _input_port_rect.getPosition().y + _input_port_rect.getGlobalBounds().height + 50);
        }
    } else {
        for (int i = 0; (size_t)i < _buttons_sprites.size(); i++)
            if (_buttons_tags[i] != "start2")
                _buttons_sprites[i].setPosition(_window->getSize().x / 2, _window->getSize().y / 2 + (i * 100 * _button_init_size.y));
            else
                _buttons_sprites[i].setPosition(40000, 40000);
        _input_host.setPosition(40000, 40000);
        _input_host_rect.setPosition(40000, 40000);
        _input_port.setPosition(40000, 40000);
        _input_port_rect.setPosition(40000, 40000);
        _ip_text.setPosition(40000, 40000);
        _port_text.setPosition(40000, 40000);
    }
}

void Menu::reset_pos(void)
{
    if (_param) {
        _input_host_rect.setPosition(_window->getSize().x / 2 - _input_host_rect.getGlobalBounds().width / 2, _window->getSize().y / 2 - _input_host_rect.getGlobalBounds().height);
        _input_host.setPosition(_window->getSize().x / 2 - _input_host.getGlobalBounds().width / 2, _window->getSize().y / 2 - _input_host_rect.getGlobalBounds().height + _input_host_rect.getGlobalBounds().height / 2 - _input_host.getGlobalBounds().height / 2);
        _ip_text.setPosition(_window->getSize().x / 2 - _ip_text.getGlobalBounds().width / 2, _input_host_rect.getPosition().y - (_input_host_rect.getGlobalBounds().height / 3));

        _input_port_rect.setPosition(_window->getSize().x / 2 - _input_port_rect.getGlobalBounds().width / 2, _window->getSize().y / 2 + _input_port_rect.getGlobalBounds().height);
        _input_port.setPosition(_window->getSize().x / 2 - _input_port.getGlobalBounds().width / 2, _window->getSize().y / 2 + _input_port_rect.getGlobalBounds().height + _input_port_rect.getGlobalBounds().height / 2 - _input_port.getGlobalBounds().height / 2);
        _port_text.setPosition(_window->getSize().x / 2 - _port_text.getGlobalBounds().width / 2, _input_port_rect.getPosition().y - (_input_port_rect.getGlobalBounds().height / 3));
        for (int i = 0; (size_t)i < _buttons_sprites.size(); i++) {
            _buttons_sprites[i].setPosition(40000, 10000);
            if (_buttons_tags[i] == "start2")
                _buttons_sprites[i].setPosition(_input_port_rect.getPosition().x + _input_port_rect.getGlobalBounds().width / 2 - _buttons_sprites[i].getGlobalBounds().width / 2, _input_port_rect.getPosition().y + _input_port_rect.getGlobalBounds().height + 50);
        }
    } else {
        for (int i = 0; (size_t)i < _buttons_sprites.size(); i++)
            if (_buttons_tags[i] != "start2")
                _buttons_sprites[i].setPosition(_window->getSize().x / 2, _window->getSize().y / 2 + (i * 100 * _button_init_size.y));
            else
                _buttons_sprites[i].setPosition(40000, 40000);
        _input_host.setPosition(40000, 40000);
        _input_host_rect.setPosition(40000, 40000);
        _input_port.setPosition(40000, 40000);
        _input_port_rect.setPosition(40000, 40000);
        _ip_text.setPosition(40000, 40000);
        _port_text.setPosition(40000, 40000);
    }
}

void Menu::menu_run(void)
{
    _window->setFramerateLimit(60);
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                _window->setView(sf::View(visibleArea));
                _background.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _title.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _title.setPosition((_window->getSize().x / 2) - (_title.getGlobalBounds().width / 2), 0);
                for (int i = 0; (size_t)i < _buttons_sprites.size(); i++)
                    _button_init_size = sf::Vector2f(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _help_menu.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                if (_help_menu.getPosition().x != 40000)
                    _help_menu.setPosition(_window->getSize().x / 2 - _help_menu.getGlobalBounds().width / 2, _window->getSize().y / 2 - _help_menu.getGlobalBounds().height / 2);
                _input_host_rect.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _input_port_rect.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _input_host.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _input_port.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _ip_text.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
                _port_text.setScale(float(event.size.width) / float(_background_texture.getSize().x), float(event.size.height) / float(_background_texture.getSize().y));
            }
            if (event.type == sf::Event::Closed) {
                _window->close();
                exit(0);
            }
            if (event.type == sf::Event::MouseMoved ||
                event.type == sf::Event::MouseButtonPressed ||
                event.type == sf::Event::MouseButtonReleased ||
                event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::TextEntered ||
                event.type == sf::Event::KeyReleased)
                buttons_handling(event);
        }
        menu_draw();
        _window->display();
    }
}
