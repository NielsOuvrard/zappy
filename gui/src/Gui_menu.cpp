/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Gui_menu
*/

#include "Gui.hpp"


void Gui::menu_texture(void)
{
    if (!_texture.loadFromFile("gui/assets/menu.png"))
        exit(84);

    _sprite.setTexture(_texture);
    if (!_font.loadFromFile("gui/assets/font.ttf"))
        exit(84);

    _text.setFont(_font);
    _text.setString("Press Enter to start");
    _text.setCharacterSize(50);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(700, 800);

    _window->draw(_sprite);
    _window->draw(_text);
    _window->display();
}

void Gui::menu_run(void)
{
    sf::RenderWindow menu(sf::VideoMode(1920, 1080), "Menu");
    _window = &menu;

    _window->setFramerateLimit(60);
    while(_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
            if (event.key.code == sf::Keyboard::Enter) {
                run();
            }
        }
        menu_texture();
    }
}