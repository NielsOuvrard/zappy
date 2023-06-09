/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

// implement log

Gui::Gui(std::string data)
{
    bool size_found = false;
    while (std::string::npos != data.find("\n") && !size_found)
    {
        std::string line = data.substr(0, data.find("\n"));
        // std::cout << "- " << line << std::endl;
        if (line.find("msz") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            std::string y = values.substr(values.find(" ") + 1);
            _size_x = std::stoi(x);
            _size_y = std::stoi(y);
            _map = new t_tile *[_size_x];
            for (int i = 0; i < _size_x; i++)
            {
                _map[i] = new t_tile[_size_y];
                for (int j = 0; j < _size_y; j++)
                {
                    _map[i][j] = (t_tile){0, 0, 0, 0, 0, 0, 0};
                }
            }
            size_found = true;
        }
    }

    _zoom = 1.0f;

    _shift_x = 0;
    _shift_y = 500;

    _speed_x = 0;
    _speed_y = 0;

    _move_right = false;
    _move_up = false;
    _move_left = false;
    _move_down = false;

    _eggs = std::vector<t_egg>();
}

Gui::~Gui()
{
}
