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

void Gui::draw_players()
{
    // to remove, put in function draw_map
    for (size_t i = 0; i < _eggs.size(); i++)
    {
        _sprites[ID_EGG].setPosition(
            (_shift_x + _eggs[i].x * 64 + _eggs[i].y * 64 + 64) * _zoom,
            (_shift_y + _eggs[i].y * 32 - _eggs[i].x * 32) * _zoom);
        _textures[ID_EGG].setSmooth(false);
        _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
        _sprites[ID_EGG].setScale(_zoom * 0.75, _zoom * 0.75);
        _window->draw(_sprites[ID_EGG]);
    }
    for (size_t i = 0; i < _players.size(); i++)
    {
        int height = 0;
        if (_players[i].y == _selected_tile_y && _players[i].x == _selected_tile_x)
            height = _height_selected_tile;
        _sprites[ID_PLAYER].setPosition(
            (_shift_x + _players[i].x * 64 + _players[i].y * 64 + 32) * _zoom,
            (_shift_y + _players[i].y * 32 - _players[i].x * 32 - 32 - height) * _zoom);
        _textures[ID_PLAYER].setSmooth(false);
        _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
        _sprites[ID_PLAYER].setScale(5 * _zoom, 5 * _zoom);
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

        _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
            SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
            1 * SIZE_PLAYER_Y, SIZE_PLAYER_X, SIZE_PLAYER_Y));
        _window->draw(_sprites[ID_PLAYER]);
    }
}

float Gui::draw_stone(int i, int j, int pos_x, int pos_y)
{
    int height = 0;
    if (i == _selected_tile_y && j == _selected_tile_x)
        height = _height_selected_tile;
    _sprites[ID_STONE].setPosition((_shift_x + j * 64 + i * 64 + 32) * _zoom, (_shift_y + i * 32 - j * 32 - 32 - height) * _zoom);
    _sprites[ID_STONE].setTextureRect(sf::IntRect(pos_x * SIZE_STONE, pos_y * SIZE_STONE, SIZE_STONE, SIZE_STONE));
    _sprites[ID_STONE].setScale(0.125 * _zoom, 0.125 * _zoom);
    _window->draw(_sprites[ID_STONE]);
    return 1;
}

void Gui::draw_decor_map(void)
{
    // draw map decor
    for (int i = 0; i < _size_x; i++)
    {
        for (int j = _size_y - 1; j >= 0; j--)
        {
            int x = _map_decor[i][j] - 'a';
            int y = 0;
            while (x >= 10)
            {
                x -= 10;
                y++;
            }
            _sprites[ID_TILE].setTextureRect(sf::IntRect(x * 256, y * 256, 256, 256));
            int height = 0;
            if (i == _selected_tile_y && j == _selected_tile_x)
            {
                _sprites[ID_TILE].setTextureRect(sf::IntRect(0 * 256, 3 * 256, 256, 256));
                height = _height_selected_tile;
            }
            // isometric
            _sprites[ID_TILE].setPosition((_shift_x + j * 64 + i * 64) * _zoom, (_shift_y + i * 32 - j * 32 - height) * _zoom);
            _sprites[ID_TILE].setScale(0.5 * _zoom, 0.5 * _zoom);
            _window->draw(_sprites[ID_TILE]);
        }
    }
    // linear interpolation
    // draw map resources
    for (int i = 0; i < _size_x; i++)
    {
        for (int j = _size_y - 1; j >= 0; j--)
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
                if (_map[i][j].ressources[k] > 0)
                    draw_stone(i, j, in_sprite_sheet[k].x, in_sprite_sheet[k].y);
            }

            int height = 0;
            if (i == _selected_tile_y && j == _selected_tile_x)
                height = _height_selected_tile;
            if (_map[i][j].ressources[0] > 0)
            {
                // food
                _sprites[ID_FOOD].setPosition((_shift_x + j * 64 + i * 64 + 32) * _zoom, (_shift_y + i * 32 - j * 32 + 16 - height) * _zoom);
                _textures[ID_FOOD].setSmooth(false);
                _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
                _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
                _sprites[ID_FOOD].setScale(_zoom, _zoom);
                _window->draw(_sprites[ID_FOOD]);
            }

            // didn't work, don't know why
            // for (size_t i = 0; i < _eggs.size(); i++)
            // {
            //     if (_eggs[i].x == j && _eggs[i].y == i)
            //     {
            //         _sprites[ID_EGG].setPosition(
            //             (_shift_x + _eggs[i].x * 64 + _eggs[i].y * 64 + 64) * _zoom,
            //             (_shift_y + _eggs[i].y * 32 - _eggs[i].x * 32) * _zoom);
            //         _textures[ID_EGG].setSmooth(false);
            //         _sprites[ID_EGG].setTexture(_textures[ID_EGG]);
            //         _sprites[ID_EGG].setScale(_zoom * 0.75, _zoom * 0.75);
            //         _window->draw(_sprites[ID_EGG]);
            //     }
            // }
        }
    }
}
