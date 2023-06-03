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
        std::cout << "line: " << line << std::endl;
        // begin by msz
        if (line.find("msz") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            std::string y = values.substr(values.find(" ") + 1);
            _size_x = std::stoi(x);
            _size_y = std::stoi(y);
        }
        if (line.find("sgt") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            _freq = std::stoi(values);
        }
        data = data.substr(data.find("\n") + 1);
    }
    std::cout << "_size_x: " << _size_x << std::endl;
    std::cout << "_size_y: " << _size_y << std::endl;
}

Gui::~Gui()
{
}

void Gui::draw_map(void)
{
    return;
}

void Gui::run(void)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zappy");
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
            else
            {
                std::cout << "Event type: " << event.type << std::endl;
            }
        }
        window.clear();
        // window.draw(shape);
        window.display();
    }

    return;
}