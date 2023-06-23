/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Gui_menu
*/

#include "Gui.hpp"


// void Gui::menu_texture(void)
// {
//     if (!_texture.loadFromFile("gui/assets/menu.png"))
//         exit(84);

//     if (!_texture2.loadFromFile("gui/assets/setting.png"))
//         exit(84);

//     _sprite.setTexture(_texture);
//     _sprite2.setTexture(_texture2);
//     if (!_font2.loadFromFile("gui/assets/adumu.ttf"))
//         exit(84);

//     _text2.setFont(_font2);
//     _text2.setString("Press Enter to start");
//     _text2.setCharacterSize(50);
//     _text2.setFillColor(sf::Color::White);
//     _text2.setPosition(750, 800);

//     _text3.setFont(_font2);
//     _text3.setString("ZAPPY");
//     _text3.setCharacterSize(250);
//     _text3.setFillColor(sf::Color::White);
//     _text3.setPosition(600, 100);

//     _window->draw(_sprite);
//     _window->draw(_sprite2);
//     _window->draw(_text2);
//     _window->draw(_text3);
// }

// do a function that animate the sprite
// all sprite will be button and we need an hover effect will progressively scale the sprite
// hold the button pressed and release it to do the action
// on pressed button, the sprite unscaled progressively
// on release button, the sprite rescaled progressively


void Gui::menu_init(void)
{

    _button_init_size = sf::Vector2f(1.0f, 1.0f);

    sf::Texture background_texture;
    if (!background_texture.loadFromFile("gui/assets/menu.png"))
        exit(84);
    _background.setTexture(background_texture);
    _background_texture = background_texture;

    if (!_help_texture.loadFromFile("gui/assets/HELP.png"))
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
}

void Gui::menu_draw(void)
{
    _window->clear();
    _background.setTexture(_background_texture);
    _window->draw(_background);
    _window->draw(_title);
    for (int i = 0; i < _buttons_sprites.size(); i++) {
        _buttons_sprites[i].setTexture(_buttons_textures[i]);
        _window->draw(_buttons_sprites[i]);
    }
    _window->draw(_help_menu);
}

void Gui::buttons_handling(sf::Event event)
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
                    run();
                }
                else if (_buttons_tags[i] == "help") {
                    _help_menu.setPosition(_window->getSize().x / 2 - _help_menu.getGlobalBounds().width / 2, _window->getSize().y / 2 - _help_menu.getGlobalBounds().height / 2);
                }
                else if (_buttons_tags[i] == "quit") {
                    _window->close();
                }
            }
            else
                _buttons_sprites[i].setScale(_button_init_size);
        }
    }
    if (event.key.code == sf::Keyboard::Escape && _help_menu.getPosition().x != 40000)
        _help_menu.setPosition(40000, 10000);
}

void Gui::menu_run(void)
{
    sf::RenderWindow menu(sf::VideoMode(1920, 1080), "Menu");
    _window = &menu;

    _menuisopen = false;

    _window->setFramerateLimit(60);
    menu_init();
    while(_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
            buttons_handling(event);
        }
        menu_draw();
        _window->display();
    }
}