/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

void Gui::player(void)
{
    _window->setView(*_view_player);
    // * BACKGROUND 500 x 700
    _sprites[ID_BACKGROUND].setPosition(0, 0);
    _sprites[ID_BACKGROUND].setColor(sf::Color(255, 255, 255, 255 * 0.8));
    _sprites[ID_BACKGROUND].setTexture(_textures[ID_BACKGROUND]);
    _sprites[ID_BACKGROUND].setScale(1.2, 1.5);
    _window->draw(_sprites[ID_BACKGROUND]);

    _text.setFillColor(sf::Color::Black);

    _text.setPosition(250, 350);
    _window->draw(_text);

    if (_players.size() == 0)
        return;

    int id = 0;
    int orientation = _players[id].orientation;
    if (orientation == 2)
        orientation = 0;
    else if (orientation == 4)
        orientation = 2;
    else if (orientation == 3)
        orientation = 3;
    else if (orientation == 1)
        orientation = 1;
    _sprites[ID_PLAYER].setPosition(0, 0);
    _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
    int team_shift = (_players[id].team % 3) * 4;
    std::cout << "Y = " << ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y) << std::endl;
    _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
        SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
        ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y), SIZE_PLAYER_X, SIZE_PLAYER_Y));
    _sprites[ID_PLAYER].setScale(5, 5);
    _window->draw(_sprites[ID_PLAYER]);
    _view_player->setCenter(250, 350);
}
// 110 - 132 - 154
