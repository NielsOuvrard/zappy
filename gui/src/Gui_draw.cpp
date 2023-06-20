/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define SIZE_PLAYER_X 16
#define SIZE_PLAYER_Y 22

void Gui::draw_players(int y, int x)
{
    sf::Color color_according_to_level[8] = {
        sf::Color(255, 255, 255),
        sf::Color(255, 255, 0),
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255),
        sf::Color(255, 0, 255),
        sf::Color(0, 255, 255),
        sf::Color(10, 10, 10),
    };
    int height = 0;
    if (y - DECOR_SIZE == _selected_tile_y && x - DECOR_SIZE == _selected_tile_x)
        height = _height_selected_tile;
    for (size_t i = 0; i < _players.size(); i++)
    {
        if (_players[i].y == y - DECOR_SIZE && _players[i].x == x - DECOR_SIZE)
        {
            _sprites[ID_PLAYER].setPosition(
                ((_players[i].x + DECOR_SIZE) * 64 + (_players[i].y + DECOR_SIZE) * 64 + 32),
                ((_players[i].y + DECOR_SIZE) * 32 - (_players[i].x + DECOR_SIZE) * 32 - 32 - height));
            _textures[ID_PLAYER].setSmooth(false);
            _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
            _sprites[ID_PLAYER].setScale(5, 5);
            int orientation = _players[i].orientation;
            if (orientation == 2)
                orientation = 0;
            else if (orientation == 4)
                orientation = 2;
            else if (orientation == 3)
                orientation = 3;
            else if (orientation == 1)
                orientation = 1;

            // recive orientation is oriented like this:
            // 1 = S
            // 2 = E
            // 3 = N
            // 4 = W

            // Sprite sheet is oriented like this:
            // 1 = S
            // 0 = E
            // 3 = N
            // 2 = W
            _sprites[ID_PLAYER].setColor(color_according_to_level[_players[i].level - 1]);
            _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
                SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
                1 * SIZE_PLAYER_Y, SIZE_PLAYER_X, SIZE_PLAYER_Y));
            _window->draw(_sprites[ID_PLAYER]);
        }
    }
    for (size_t i = 0; i < _eggs.size(); i++)
    {
        if (_eggs[i].y == y && _eggs[i].x == x)
        {
            _sprites[ID_EGG].setPosition(
                (_eggs[i].x * 64 + _eggs[i].y * 64 + 64),
                (_eggs[i].y * 32 - _eggs[i].x * 32 - height));
            _textures[ID_EGG].setSmooth(false);
            _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
            _sprites[ID_EGG].setScale(0.75, 0.75);
            _window->draw(_sprites[ID_EGG]);
        }
    }
}

void Gui::draw_stone(int i, int j, int pos_x, int pos_y)
{
    int i_map = i - DECOR_SIZE;
    int j_map = j - DECOR_SIZE;
    int height = 0;
    if (i_map == _selected_tile_y && j_map == _selected_tile_x)
        height = _height_selected_tile;
    _sprites[ID_STONE].setPosition((j * 64 + i * 64 + 32), (i * 32 - j * 32 - 32 - height));
    _sprites[ID_STONE].setTextureRect(sf::IntRect(pos_x * SIZE_STONE, pos_y * SIZE_STONE, SIZE_STONE, SIZE_STONE));
    _sprites[ID_STONE].setScale(0.125, 0.125);
    _window->draw(_sprites[ID_STONE]);
}

void Gui::draw_stones(int i, int j)
{
    sf::Vector2u in_sprite_sheet[7] = {
        {0, 0},  // food
        {1, 0},  // linemate
        {1, 1},  // deraumere
        {1, 3},  // sibur
        {1, 2},  // mendiane
        {12, 5}, // phiras
        {2, 4}   // thystame
    };
    for (int k = 1; k < 7; k++)
    {
        if (_map[i - DECOR_SIZE][j - DECOR_SIZE].ressources[k] > 0)
        {
            draw_stone(i, j, in_sprite_sheet[k].x, in_sprite_sheet[k].y);
            return;
        }
    }
}

void Gui::draw_map_tile(int i, int j, int tile)
{
    int x = tile - 'a';
    int y = 0;
    while (x >= 10)
    {
        x -= 10;
        y++;
    }
    _sprites[ID_TILE].setTextureRect(sf::IntRect(x * SIZE_PX_TILE, y * SIZE_PX_TILE, SIZE_PX_TILE, SIZE_PX_TILE));
    int height = 0;
    if (i - DECOR_SIZE == _selected_tile_y && j - DECOR_SIZE == _selected_tile_x)
    {
        _sprites[ID_TILE].setTextureRect(sf::IntRect(0 * SIZE_PX_TILE, 3 * SIZE_PX_TILE, SIZE_PX_TILE, SIZE_PX_TILE));
        height = _height_selected_tile;
    }
    // isometric
    _sprites[ID_TILE].setPosition((j * 64 + i * 64), (i * 32 - j * 32 - height));
    _sprites[ID_TILE].setScale(0.5, 0.5);
    _window->draw(_sprites[ID_TILE]);

    // * TREE
    if (tile == 115 && i % 7 == 0 && j % 4 == 0)
    {
        _sprites[ID_TREE].setTexture(_textures[ID_TREE]);
        _sprites[ID_TREE].setTextureRect(sf::IntRect(2 * SIZE_PX_TILE, 0, SIZE_PX_TILE, 512));
        _sprites[ID_TREE].setPosition(
            (j * 64 + i * 64),
            (i * 32 - j * 32 - 64 - (512 / 4)));
        _sprites[ID_TREE].setScale(0.5, 0.5);
        _window->draw(_sprites[ID_TREE]);
    }
}

void Gui::draw_map_half_tile(int i, int j, int tile)
{
    int x = tile - '0';
    if (x == 11 && (i % 5 == _waves % 5))
        x = 18;
    if (x == 11 && (j + i) % 5 == _waves % 5)
        x = 13;
    int y = 0;
    while (x >= 10)
    {
        x -= 10;
        y++;
    }
    _sprites[ID_HALF_TILE].setTexture(_textures[ID_HALF_TILE]);
    _sprites[ID_HALF_TILE]
        .setTextureRect(sf::IntRect(x * SIZE_PX_TILE, y * SIZE_PX_HALF_TILE, SIZE_PX_TILE, SIZE_PX_HALF_TILE));
    // isometric
    _sprites[ID_HALF_TILE].setPosition(
        (j * 64 + i * 64),
        (i * 32 - j * 32 + 32));
    _sprites[ID_HALF_TILE].setScale(0.5, 0.5);
    _window->draw(_sprites[ID_HALF_TILE]);

    // * TREE
    if (tile == 'M' && i % 7 == 0 && j % 7 == 0)
    {
        _sprites[ID_TREE].setTexture(_textures[ID_TREE]);
        _sprites[ID_TREE].setTextureRect(sf::IntRect(2 * SIZE_PX_TILE, 0, SIZE_PX_TILE, 512));
        _sprites[ID_TREE].setPosition(
            (j * 64 + i * 64),
            (i * 32 - j * 32 - 32 - (512 / 4)));
        _sprites[ID_TREE].setScale(0.5, 0.5);
        _window->draw(_sprites[ID_TREE]);
    }
}

void Gui::draw_map(void)
{
    for (int i = 0; i < _map_decor.size(); i++)
    {
        for (int j = _map_decor[i].size() - 1; j >= 0; j--)
        {
            // * DRAW TILE
            if (_map_decor[i][j] >= 'a')
                draw_map_tile(i, j, _map_decor[i][j]);
            else
                draw_map_half_tile(i, j, _map_decor[i][j]);
            if (i >= DECOR_SIZE && i < DECOR_SIZE + _size_y && j >= DECOR_SIZE && j < DECOR_SIZE + _size_x)
            {
                // * DRAW STONES
                draw_stones(i, j);

                // * DRAW FOOD
                int i_map = i - DECOR_SIZE;
                int j_map = j - DECOR_SIZE;
                int height = 0;
                if (i_map == _selected_tile_y && j_map == _selected_tile_x)
                    height = _height_selected_tile;
                if (_map[i_map][j_map].ressources[0] > 0)
                {
                    _sprites[ID_FOOD].setPosition(
                        (j * 64 + i * 64 + 32),
                        (i * 32 - j * 32 + 16 - height));
                    _textures[ID_FOOD].setSmooth(false);
                    _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
                    _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
                    _sprites[ID_FOOD].setScale(1, 1);
                    _window->draw(_sprites[ID_FOOD]);
                }
                // * DRAW PLAYERS
                draw_players(i, j);
            }
        }
    }
}

void Gui::draw_particles(void)
{
    for (size_t i = 0; i < _particles.size(); i++)
    {
        // TODO height ?
        sf::CircleShape circle(7 + _particles[i].lifetime * 0.5);
        std::cout << "part [" << i << "] pos: " << _particles[i].pos.x << " " << _particles[i].pos.y << std::endl;
        circle.setPosition(_particles[i].pos.x, _particles[i].pos.y);
        circle.setFillColor(_particles[i].color);
        _window->draw(circle);
    }
}

// linear interpolation
