/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

Gui::Gui(std::string data, Network *network) : _network(network)
{
    bool size_found = false;
    while (std::string::npos != data.find("\n") && !size_found)
    {
        std::string line = data.substr(0, data.find("\n"));
        if (line.find("msz") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            std::string y = values.substr(values.find(" ") + 1);
            _size_x = std::stoi(x);
            _size_y = std::stoi(y);
            _map = new t_tile *[_size_y];
            for (int i = 0; i < _size_y; i++)
            {
                _map[i] = new t_tile[_size_x];
                for (int j = 0; j < _size_x; j++)
                {
                    _map[i][j] = (t_tile){0, 0, 0, 0, 0, 0, 0};
                }
            }
            size_found = true;
        }
    }

    _zoom = 1.0f;

    _waves = 0;

    _height_selected_tile = 0;
    _up_selected_tile = false;

    _shift_x = -2400;
    _shift_y = 900;

    _speed_x = 0;
    _speed_y = 0;

    _pos = sf::Vector2f(4000, 0);

    _selected_tile_x = 0;
    _selected_tile_y = 0;

    _move_right = false;
    _move_down = false;
    _move_left = false;
    _move_up = false;

    _interface_show = true;
    _interface_center_value = 0;

    _eggs = std::vector<t_egg>();
    _font = sf::Font();
    _font.loadFromFile("gui/assets/font.ttf");
    _text = sf::Text("Hello World", _font);
}

Gui::~Gui()
{
    for (int i = 0; i < _size_y; i++)
    {
        delete[] _map[i];
    }
    delete[] _map;
}
