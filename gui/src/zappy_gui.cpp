/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"

int zappy_gui(int ac, char **av)
{
    for (int i = 0; i < ac; i++)
    {
        std::cout << av[i] << std::endl;
    }
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zappy");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // window.draw(shape);
        window.display();
    }

    return 0;
}
