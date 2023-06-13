/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"
#include <cmath>

/*
the map

.......
.......
..***..
..***..
..***..
..***..
.......
.......

*/
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

    // str of 15 * '-11' with memset

    int size_island = _size_y > _size_x ? _size_y : _size_x;

    std::string water_all((2 * DECOR_SIZE) + _size_x, ';');

    std::string sand(1, 'M');
    std::string sand_middle(_size_x, 'M');

    std::cout << LOG_GUI("sand: " + sand_middle);

    for (int i = 0; i < (2 * DECOR_SIZE) + _size_y; i++)
        _map_decor.push_back(water_all);

    // for (int i = 0; i < (2 * DECOR_SIZE) + _size_y; i++)
    //     for (int j = 0; j < (2 * DECOR_SIZE) + _size_x; j++)
    //         _map_decor[i][j] += i % 4;

    int middle_x = ((2 * DECOR_SIZE) + _size_x) / 2;
    int middle_y = ((2 * DECOR_SIZE) + _size_y) / 2;

    for (int i = 0; i < (2 * DECOR_SIZE) + _size_y; i++)
        for (int j = 0; j < (2 * DECOR_SIZE) + _size_x; j++)
            if (sqrt(pow((j - middle_x), 2) + pow((i - middle_y), 2)) < _size_x * 1.1)
                _map_decor[i][j] = 'M';

    for (int i = 0; i < (2 * DECOR_SIZE) + _size_y; i++)
        for (int j = 0; j < (2 * DECOR_SIZE) + _size_x; j++)
            if (sqrt(pow((j - middle_x), 2) + pow((i - middle_y), 2)) < _size_x * 0.8)
                _map_decor[i][j] = 'a' + 18;

    for (int i = 0; i < _size_y; i++)
    {
        std::getline(ifs, line);
        // _map_decor.push_back(line.substr(0, _size_x));
        for (int j = 0; j < _size_x; j++)
            _map_decor[DECOR_SIZE + i][DECOR_SIZE + j] = line[j];
        // std::cout << LOG_GUI(line);
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

    // 30 + _size_x
    // 30 + _size_y
    // for (int i = 0; )
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
    // _sprites[11].setScale(1, 1);

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
