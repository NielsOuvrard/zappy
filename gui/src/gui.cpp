/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "gui.hpp"

Gui::Gui(std::string data)
{
    // parse data
    while (std::string::npos != data.find("\n"))
    {
        std::string line = data.substr(0, data.find("\n"));
        std::cout << "- " << line << std::endl;
        // begin by msz
        if (line.find("msz") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            std::string y = values.substr(values.find(" ") + 1);
            _size_x = std::stoi(x);
            _size_y = std::stoi(y);
            std::cout << "x = " << _size_x << " y = " << _size_y << std::endl;
            for (int i = 0; i < _size_x; i++)
            {
                std::cout << "i = " << _size_y << std::endl;
                _map[i] = new t_tile[_size_y];
                std::cout << "i = " << i << std::endl;
                for (int j = 0; j < _size_y; j++)
                {
                    std::cout << "i = " << i << " j = " << j << std::endl;
                    _map[i][j] = (t_tile){0, 0, 0, 0, 0, 0, 0};
                }
            }
        }
        if (line.find("sgt") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            _freq = std::stoi(values);
        }
        if (line.find("bct") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string food = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string linemate = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string deraumere = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string sibur = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string mendiane = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string phiras = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string thystame = values.substr(0, values.find(" "));
            _map[std::stoi(x)][std::stoi(y)] = (t_tile){
                std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame)};
        }
        data = data.substr(data.find("\n") + 1);
    }
    std::cout << "_size_x: " << _size_x << std::endl;
    std::cout << "_size_y: " << _size_y << std::endl;
    std::cout << "freq: " << _freq << std::endl;
}

Gui::~Gui()
{
}

void Gui::draw_map(sf::RenderWindow &window)
{
    for (int i = 0; i < _size_x; i++)
    {
        for (int j = 0; j < _size_y; j++)
        {
            _tile.setPosition(i * 64, j * 64);
            window.draw(_tile);
            if (_map[i][j].linemate > 0)
            {
                _food.setPosition(i * 64, j * 64);
                window.draw(_food);
            }
        }
    }
    return;
}

void Gui::run(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    sf::Texture texture;
    if (!texture.loadFromFile("gui/assets/tile_64.png"))
    {
        std::cout << "Error loading texture" << std::endl;
    }
    _tile.setTexture(texture);
    sf::Texture texture2;
    if (!texture2.loadFromFile("gui/assets/food_64.png"))
    {
        std::cout << "Error loading texture" << std::endl;
    }
    _food.setTexture(texture2);

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // else
            // {
            //     std::cout << "Event type: " << event.type << std::endl;
            // }
        }
        window.clear();
        draw_map(window);
        // window.draw(shape);
        window.display();
    }

    return;
}