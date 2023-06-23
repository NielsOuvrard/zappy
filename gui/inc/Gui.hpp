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
    // food, linemate, deraumere, sibur, mendiane, phiras, thystame
    int ressources[7];
} t_tile;

typedef struct s_player
{
    int id;
    int x;
    int y;
    int orientation;
    int level;
    std::string team;
    int inventory[7];
} t_player;

typedef struct s_egg
{
    int id;
    int x;
    int y;
    int player_id;
} t_egg;

#define ID_TILE 0
#define ID_STONE 1
#define ID_FOOD 2
#define ID_PLAYER 3
#define ID_EGG 4

#define SIZE_TILE 64
#define SIZE_STONE 512
#define SIZE_FOOD 32

class Gui
{
public:
    Gui(std::string data);
    ~Gui();
    void run(void);
    bool fill_map(std::string data);

private:
    void draw_map(void);
    void draw_players(size_t y, size_t x);
    void load_textures(void);
    void load_map(void);
    void draw_decor_map(void);
    void move_map(sf::Event event);
    void interface(void);
    void draw_stones(int i, int j);
    void draw_stone(int i, int j, int pos_x, int pos_y);
    void perlin_noise(void);
    sf::RenderWindow *_window;

    // data
    t_tile **_map;
    std::vector<std::string> _map_decor;
    std::vector<std::string> _teams;
    std::vector<t_player> _players;
    std::vector<t_egg> _eggs;
    std::string _ressources[7] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

    //position
    sf::Vector2f _pos;
    sf::Vector2i clickPosition;

    // draw menu
    sf::Text _text;
    sf::Font _font;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Texture> _textures;

    int _selected_tile_x;
    int _selected_tile_y;

    int _height_selected_tile;
    bool _up_selected_tile;

    // server params
    int _freq;
    int _size_x;
    int _size_y;

    // window params
    int _shift_x;
    int _shift_y;
    float _zoom;
    float _speed_x;
    float _speed_y;
    bool _move_right;
    bool _move_down;
    bool _move_left;
    bool _move_up;
};
