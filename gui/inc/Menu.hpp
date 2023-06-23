/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-kenan.blasius
** File description:
** Menu
*/

#pragma once
#include "zappy_gui.hpp"

class Menu {
    public:
        Menu(std::string ip, std::string port);
        ~Menu();

        void menu_draw(void);
        void buttons_handling(sf::Event event);
        void menu_run(void);

        std::string get_ip(void) const { return _ip; };
        std::string get_port(void) const { return _port; };

    private:
        // draw main menu
        sf::Sprite _background;
        sf::Texture _background_texture;
        sf::Sprite _help_menu;
        sf::Texture _help_texture;
        sf::Text _title;
        sf::Font _adumu;
        sf::Text _input_host;
        sf::RectangleShape _input_host_rect;
        sf::Text _input_port;
        sf::RectangleShape _input_port_rect;
        std::vector<sf::Sprite> _buttons_sprites;
        std::vector<sf::Texture> _buttons_textures;
        std::vector<std::string> _buttons_tags;
        std::vector<bool> _buttons_pressed;
        sf::Vector2f _button_init_size;
        bool _param;
        bool _input_host_selected;
        bool _input_port_selected;
        std::string _ip;
        std::string _port;
        sf::RenderWindow *_window;
        sf::Text _ip_text;
        sf::Text _port_text;
};
