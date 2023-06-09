/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

void Gui::load_map(void)
{
    std::ofstream myfile;
    std::ifstream ifs;
    std::string line;
    ifs.open("gui/assets/map.txt", std::ifstream::in);
    if (!ifs.good())
    {
        std::cout << "Error opening assets.txt" << std::endl;
        exit(84);
    }
    std::cout << LOG_GUI("Loading map");

    while (std::getline(ifs, line))
    {
        _map_decor.push_back(line);
        std::cout << LOG_GUI(line);
    }
}

void Gui::load_textures(void)
{
    std::ofstream myfile;
    std::ifstream ifs;
    std::string line;
    ifs.open("gui/assets/assets.txt", std::ifstream::in);
    if (!ifs.good())
    {
        std::cout << "Error opening assets.txt" << std::endl;
        exit(84);
    }

    while (std::getline(ifs, line))
    {
        sf::Texture texture;
        if (!texture.loadFromFile("gui/assets/" + line))
        {
            std::cout << "Error loading texture " << line << std::endl;
        }
        _sprites.push_back(sf::Sprite());
        _textures.push_back(texture);
    }
    _sprites[8].setOrigin(32, 32);

    _sprites[ID_TILE].setTexture(_textures[ID_TILE]);
    _sprites[ID_TILE].setTextureRect(sf::IntRect(0, 0, 256, 256));
    _sprites[ID_TILE].setScale(0.5, 0.5);

    _sprites[ID_STONE].setTexture(_textures[ID_STONE]);
    _sprites[ID_STONE].setTextureRect(sf::IntRect(0, 0, SIZE_STONE, SIZE_STONE));
    _sprites[ID_STONE].setScale(0.125, 0.125);

    _textures[ID_FOOD].setSmooth(false);
    _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
    _sprites[ID_FOOD].setTextureRect(sf::IntRect(2, 1, SIZE_FOOD, SIZE_FOOD));
    // _sprites[11].setScale(1, 1);

    _textures[ID_PLAYER].setSmooth(false);
    _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
    _sprites[ID_PLAYER].setScale(5, 5);

    _textures[ID_EGG].setSmooth(false);
    _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
    _sprites[ID_EGG].setScale(5, 5);
}
