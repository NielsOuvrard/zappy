/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"
// 500 - 2 * 110 = 280
void Gui::player(void)
{
    _window->setView(*_view_player);
    // * BACKGROUND 500 x 700
    _sprites[ID_BACKGROUND].setOrigin(0, 0);
    _sprites[ID_BACKGROUND].setPosition(-110, -110);
    _sprites[ID_BACKGROUND].setColor(sf::Color(255, 255, 255, 255 * 0.8));
    _sprites[ID_BACKGROUND].setTexture(_textures[ID_BACKGROUND]);
    _sprites[ID_BACKGROUND].setScale(1, 1);
    _window->draw(_sprites[ID_BACKGROUND]);

    _text.setFillColor(sf::Color::Black);
    _text.setString("Player [" + std::to_string(_selected_player) + "/" + std::to_string(_players.size()) + "]");
    _text.setPosition(0, 0);
    _window->draw(_text);

    if (_players.size() == 0)
        return;

    int orientation = _players[_selected_player].orientation;
    if (orientation == 2)
        orientation = 0;
    else if (orientation == 4)
        orientation = 2;
    else if (orientation == 3)
        orientation = 3;
    else if (orientation == 1)
        orientation = 1;
    _sprites[ID_PLAYER].setPosition(280 / 2, 100);
    _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);

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
    _sprites[ID_PLAYER].setColor(color_according_to_level[_players[_selected_player].level - 1]);

    int team_shift = (_players[_selected_player].team % 3) * 4;
    std::cout << "Y = " << ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y) << std::endl;
    _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
        SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
        ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y), SIZE_PLAYER_X, SIZE_PLAYER_Y));
    _sprites[ID_PLAYER].setScale(5, 5);

    _window->draw(_sprites[ID_PLAYER]);
}
// 110 - 132 - 154
