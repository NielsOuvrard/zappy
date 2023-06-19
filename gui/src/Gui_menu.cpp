/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Gui_menu
*/

#include "Gui.hpp"

void Gui::set_pos(void)
{
    _sprite2.setPosition(0, 0);
}

void Gui::draw_help(void)
{
    if (!_texture3.loadFromFile("gui/assets/HELP.png"))
        exit(84);

    _sprite3.setTexture(_texture3);
    _sprite3.setPosition(400, 100);

    _window->draw(_sprite3);
}


void Gui::menu_texture(void)
{
    if (!_texture.loadFromFile("gui/assets/menu.png"))
        exit(84);

    if (!_texture2.loadFromFile("gui/assets/setting.png"))
        exit(84);

    _sprite.setTexture(_texture);
    _sprite2.setTexture(_texture2);
    if (!_font.loadFromFile("gui/assets/tiki.ttf"))
        exit(84);

    _text.setFont(_font);
    _text.setString("Press Enter to start");
    _text.setCharacterSize(50);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(750, 800);

    _text2.setFont(_font);
    _text2.setString("ZAPPY");
    _text2.setCharacterSize(250);
    _text2.setFillColor(sf::Color::White);
    _text2.setPosition(600, 100);

    _window->draw(_sprite);
    _window->draw(_sprite2);
    _window->draw(_text);
    _window->draw(_text2);

}


void Gui::menu_run(void)
{
    sf::RenderWindow menu(sf::VideoMode(1920, 1080), "Menu");
    _window = &menu;

    _menuisopen = false;

    _window->setFramerateLimit(60);
    while(_window->isOpen()) {
        sf::Event event;
        menu_texture();
        if (_menuisopen == true) {
            draw_help();
        }
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonPressed) {
                clickPosition = sf::Mouse::getPosition(*_window);
                if (_sprite2.getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                    _menuisopen = !_menuisopen;
                }
            }
            if (event.key.code == sf::Keyboard::Enter) {
                run();
            }
        }
        _window->display();
    }
}