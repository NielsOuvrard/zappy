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
    if (_selected_player >= _players.size())
        _selected_player = _players.size() - 1;
    _window->setView(*_view_player);
    // * BACKGROUND 500 x 700
    _sprites[ID_BACKGROUND].setOrigin(0, 0);
    _sprites[ID_BACKGROUND].setPosition(-110, -110);
    _sprites[ID_BACKGROUND].setColor(sf::Color(255, 255, 255, 255 * 0.8));
    _sprites[ID_BACKGROUND].setTexture(_textures[ID_BACKGROUND]);
    _sprites[ID_BACKGROUND].setScale(1, 1);
    _window->draw(_sprites[ID_BACKGROUND]);

    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(30);
    if (_players.size() == 0)
        _text.setString("No player");
    else
        _text.setString("Player [" + std::to_string(_selected_player + 1) + "/" + std::to_string(_players.size()) + "]");
    _text.setPosition(10, 10);
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
    _sprites[ID_PLAYER].setPosition(160, 75);
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
    // std::cout << "Y = " << ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y) << std::endl;
    _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
        SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
        ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y),
        SIZE_PLAYER_X,
        SIZE_PLAYER_Y));
    _sprites[ID_PLAYER].setScale(5, 5);

    if (_waves % 3 == 1)
        // add 1 to the y pos of texture rect
        _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
            SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
            ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y) + 1,
            SIZE_PLAYER_X,
            SIZE_PLAYER_Y));
    else if (_waves % 3 == 2)
        // add 4 to the y pos of texture rect
        _sprites[ID_PLAYER].setTextureRect(sf::IntRect(
            SIZE_PLAYER_X + (2 * orientation * SIZE_PLAYER_X),
            ((1 + (_waves % 3)) * SIZE_PLAYER_Y) + (team_shift * SIZE_PLAYER_Y) + 4,
            SIZE_PLAYER_X,
            SIZE_PLAYER_Y));

    _window->draw(_sprites[ID_PLAYER]);

    sf::Text posText;
    posText.setFont(_font);
    posText.setCharacterSize(20);
    posText.setFillColor(sf::Color::Black);
    posText.setString("X: " + std::to_string(_players[_selected_player].x) + " Y: " + std::to_string(_players[_selected_player].y));
    posText.setPosition(10, 50);
    _window->draw(posText);

    sf::Text levelText;
    levelText.setFont(_font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Black);
    levelText.setString("Level: " + std::to_string(_players[_selected_player].level));
    levelText.setPosition(10, 80);
    _window->draw(levelText);

    // * INVENTORY
    sf::Text inventoryText;
    inventoryText.setFont(_font);
    inventoryText.setCharacterSize(20);
    inventoryText.setFillColor(sf::Color::Black);
    inventoryText.setString("Inventory:");
    inventoryText.setPosition(10, 130);
    _window->draw(inventoryText);

    sf::Vector2u in_sprite_sheet[7] = {
        {0, 0},  // food
        {1, 0},  // linemate
        {1, 1},  // deraumere
        {1, 3},  // sibur
        {1, 2},  // mendiane
        {12, 5}, // phiras
        {2, 4}   // thystame
    };

    // * FOOD
    _sprites[ID_FOOD].setPosition(20, 170);
    _textures[ID_FOOD].setSmooth(false);
    _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
    _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
    _sprites[ID_FOOD].setScale(1, 1);
    _window->draw(_sprites[ID_FOOD]);

    sf::Text foodText;
    foodText.setFont(_font);
    foodText.setCharacterSize(20);
    foodText.setFillColor(sf::Color::Black);
    foodText.setString("x" + std::to_string(_players[_selected_player].inventory[0]));
    foodText.setPosition(70, 170);
    _window->draw(foodText);

    // * STONES
    for (size_t i = 1; i < 7; i++)
    {
        _sprites[ID_STONE].setPosition(10, i * 40 + 160);
        _sprites[ID_STONE].setTextureRect(sf::IntRect(in_sprite_sheet[i].x * SIZE_STONE, in_sprite_sheet[i].y * SIZE_STONE, SIZE_STONE, SIZE_STONE));
        _sprites[ID_STONE].setScale(0.1, 0.1);
        _window->draw(_sprites[ID_STONE]);


        sf::Text tmpText;
        tmpText.setFont(_font);
        tmpText.setCharacterSize(20);
        tmpText.setFillColor(sf::Color::Black);
        tmpText.setString("x" + std::to_string(_players[_selected_player].inventory[i]));
        tmpText.setPosition(70, i * 40 + 170);
        _window->draw(tmpText);
    }

    if (_players[_selected_player].is_incanting)
    {
        for (size_t i = 0; i < _player_particles.size(); i++)
        {
            sf::CircleShape circle(7 + _player_particles[i].lifetime * 0.5);
            circle.setPosition(_player_particles[i].pos.x, _player_particles[i].pos.y);
            circle.setFillColor(_player_particles[i].color);
            _window->draw(circle);
        }
    }

    // * TEAM
    sf::Text teamText;
    teamText.setFont(_font);
    teamText.setCharacterSize(15);
    teamText.setFillColor(sf::Color::Black);
    teamText.setString("Team Name:" + _players[_selected_player].team);
    teamText.setPosition(140, 170);
    _window->draw(teamText);

    sf::Text teamNameText;
    teamNameText.setFont(_font);
    teamNameText.setCharacterSize(15);
    teamNameText.setFillColor(sf::Color::Black);
    teamNameText.setString(_teams[_players[_selected_player].team]);
    teamNameText.setPosition(140, 190);
    _window->draw(teamNameText);

    // * TEAMMATES NUMBER
    sf::Text teamNbText;
    teamNbText.setFont(_font);
    teamNbText.setCharacterSize(15);
    teamNbText.setFillColor(sf::Color::Black);
    teamNbText.setString("Teammates:");
    teamNbText.setPosition(140, 230);
    _window->draw(teamNbText);
    sf::Text teamNbText2;
    teamNbText2.setFont(_font);
    teamNbText2.setCharacterSize(15);
    teamNbText2.setFillColor(sf::Color::Black);
    int teammates = 0;
    for (size_t i = 0; i < _players.size(); i++)
        if (_players[i].team == _players[_selected_player].team)
            teammates++;
    teamNbText2.setString(std::to_string(teammates));
    teamNbText2.setPosition(140, 250);
    _window->draw(teamNbText2);

    // * HIGHEST LEVEL IN TEAM
    sf::Text teamHighestText;
    teamHighestText.setFont(_font);
    teamHighestText.setCharacterSize(15);
    teamHighestText.setFillColor(sf::Color::Black);
    teamHighestText.setString("Highest Level:");
    teamHighestText.setPosition(140, 290);
    _window->draw(teamHighestText);
    sf::Text teamHighestText2;
    teamHighestText2.setFont(_font);
    teamHighestText2.setCharacterSize(15);
    teamHighestText2.setFillColor(sf::Color::Black);
    int highest = 0;
    for (size_t i = 0; i < _players.size(); i++)
        if (_players[i].team == _players[_selected_player].team && _players[i].level > highest)
            highest = _players[i].level;
    teamHighestText2.setString(std::to_string(highest));
    teamHighestText2.setPosition(140, 310);
    _window->draw(teamHighestText2);
}
// 110 - 132 - 154
