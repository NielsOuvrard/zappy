/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"
#include <cmath>

bool Gui::is_sand_center(int i, int j, int middle_x, int middle_y, float multiple)
{
    if (middle_x + multiple * _size_x > j && middle_x - multiple * _size_x < j && middle_y + multiple * _size_y > i && middle_y - multiple * _size_y < i)
    {
        // taller than wide
        if (_size_x > _size_y)
        {
            if (j > middle_x + ((_size_y / 2) - (_size_x / 2)) && j < middle_x - ((_size_y / 2) - (_size_x / 2)))
                return true;
            else if (std::pow((j - middle_x - ((_size_y / 2) - (_size_x / 2))), 2) + std::pow((i - middle_y), 2) <= std::pow(multiple * _size_y, 2))
                return true;
            else if (std::pow((j - middle_x + ((_size_y / 2) - (_size_x / 2))), 2) + std::pow((i - middle_y), 2) <= std::pow(multiple * _size_y, 2))
                return true;
        }
        else
        {
            if (i > middle_y + ((_size_x / 2) - (_size_y / 2)) && i < middle_y - ((_size_x / 2) - (_size_y / 2)))
                return true;
            else if (std::pow((j - middle_x), 2) + std::pow((i - middle_y - ((_size_x / 2) - (_size_y / 2))), 2) <= std::pow(multiple * _size_x, 2))
                return true;
            else if (std::pow((j - middle_x), 2) + std::pow((i - middle_y + ((_size_x / 2) - (_size_y / 2))), 2) <= std::pow(multiple * _size_x, 2))
                return true;
        }
    }
    return false;
}

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

    int size_island = _size_y > _size_x ? _size_y : _size_x;

    std::string water_all((2 * DECOR_SIZE) + size_island, ';');

    std::string sand(1, 'M');
    std::string sand_middle(_size_x, 'M');

    for (int i = 0; i < (2 * DECOR_SIZE) + size_island; i++)
        _map_decor.push_back(water_all);

    int middle_x = ((2 * DECOR_SIZE) + _size_x) / 2;
    int middle_y = ((2 * DECOR_SIZE) + _size_y) / 2;

    for (int i = 0; i < (2 * DECOR_SIZE) + _size_y; i++)
    {
        for (int j = 0; j < (2 * DECOR_SIZE) + _size_x; j++)
        {
            if (is_sand_center(i, j, middle_x, middle_y, 0.8))
                _map_decor[i][j] = 'a' + 18; // sand center
            else if (is_sand_center(i, j, middle_x, middle_y, 1.1))
                _map_decor[i][j] = 'M'; // sand borders
        }
    }

    for (int i = 0; i < _size_y; i++)
    {
        std::getline(ifs, line);
        for (int j = 0; j < _size_x; j++)
            _map_decor[DECOR_SIZE + i][DECOR_SIZE + j] = line[j];
    }

    // display map
    for (size_t i = 0; i < _map_decor.size(); i++)
    {
        for (size_t j = 0; j < _map_decor[i].size(); j++)
        {
            std::cout << _map_decor[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

    _sprites[ID_TILE].setTexture(_textures[ID_TILE]);
    _sprites[ID_TILE].setTextureRect(sf::IntRect(0, 0, SIZE_PX_TILE, SIZE_PX_TILE));
    _sprites[ID_TILE].setScale(0.5, 0.5);

    _sprites[ID_STONE].setTexture(_textures[ID_STONE]);
    _sprites[ID_STONE].setTextureRect(sf::IntRect(0, 0, SIZE_STONE, SIZE_STONE));
    _sprites[ID_STONE].setScale(0.125, 0.125);

    _textures[ID_FOOD].setSmooth(false);
    _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
    _sprites[ID_FOOD].setTextureRect(sf::IntRect(2, 1, SIZE_FOOD, SIZE_FOOD));

    _textures[ID_PLAYER].setSmooth(false);
    _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
    _sprites[ID_PLAYER].setScale(5, 5);

    _textures[ID_EGG].setSmooth(false);
    _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
    _sprites[ID_EGG].setScale(5, 5);

    _sprites[ID_HALF_TILE].setTexture(_textures[ID_HALF_TILE]);
    _sprites[ID_HALF_TILE].setTextureRect(sf::IntRect(0, 0, SIZE_PX_TILE, SIZE_PX_HALF_TILE));
    _sprites[ID_HALF_TILE].setScale(0.5, 0.5);

    _sprites[ID_TREE].setTexture(_textures[ID_TREE]);
    _sprites[ID_TREE].setTextureRect(sf::IntRect(0, 0, SIZE_PX_TILE, 512));
    _sprites[ID_TREE].setScale(0.5, 0.5);

    _sprites[ID_BACKGROUND].setTexture(_textures[ID_BACKGROUND]);
    _sprites[ID_BACKGROUND].setScale(0.5, 0.5);
}
