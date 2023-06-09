/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#pragma once
#include "zappy_gui.hpp"

typedef struct s_tile
{
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} t_tile;

typedef struct s_player
{
    int id;
    int x;
    int y;
    int orientation;
    int level;
    std::string team;
} t_player;

class Gui
{
public:
    Gui(std::string data);
    ~Gui();
    void run(void);
    bool fill_map(std::string data);

private:
    void draw_map(sf::RenderWindow &window);
    void draw_players(sf::RenderWindow &window);
    void load_textures(void);
    void load_map(void);
    void draw_decor_map(sf::RenderWindow &window);
    void move_map(sf::Event event);

    float good_position_x(int j, int i, int size_x, int size_y);
    float good_position_y(int j, int i, int size_x, int size_y);

    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Texture> _textures;

    t_tile **_map;
    std::vector<std::string> _map_decor;
    std::vector<std::string> _teams;
    std::vector<t_player> _players;

    int _size_x;
    int _size_y;
    int _freq;

    int _shift_x;
    int _shift_y;

    float _speed_x;
    float _speed_y;

    bool _move_right;
    bool _move_up;
    bool _move_left;
    bool _move_down;
};
