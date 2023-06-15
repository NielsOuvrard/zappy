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
#define ID_HALF_TILE 5
#define ID_TREE 6
#define ID_BACKGROUND 7

#define SIZE_TILE 64
#define SIZE_STONE 512
#define SIZE_FOOD 32

#define DECOR_SIZE 30

#define SIZE_PX_TILE 256
#define SIZE_PX_HALF_TILE 192

#define ZOOM_MAX 2
#define ZOOM_MIN 0.2

class Gui
{
public:
    Gui(std::string data);
    ~Gui();
    void run(void);
    bool fill_map(std::string data);

private:
    void draw_players(int y, int x);
    void load_textures(void);
    void load_map(void);
    void draw_map(void);
    void draw_map_tile(int i, int j, int tile);
    void draw_map_half_tile(int i, int j, int tile);
    bool is_sand_center(int i, int j, int middle_x, int middle_y, float multiple);

    // void create_outdoor_map(void);
    void move_map(sf::Event event);
    void interface(void);
    void draw_stones(int i, int j);
    void draw_stone(int i, int j, int pos_x, int pos_y);
    void perlin_noise(void);
    void move_tile(sf::Event event);

    sf::RenderWindow *_window;

    // data
    t_tile **_map;
    std::vector<std::string> _map_decor;
    std::vector<std::string> _teams;
    std::vector<t_player> _players;
    std::vector<t_egg> _eggs;
    std::string _ressources[7] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

    // draw
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Texture> _textures;
    sf::Font _font;
    sf::Text _text;

    sf::View *_view_main;
    sf::View *_view_interface;

    int _selected_tile_x;
    int _selected_tile_y;

    int _height_selected_tile;
    bool _up_selected_tile;

    // server params
    int _freq;
    int _size_x;
    int _size_y;

    size_t _waves;

    // window params
    int _shift_x;
    int _shift_y;
    float _zoom;
    float _speed_x;
    float _speed_y;

    sf::Vector2f _pos;

    bool _move_right;
    bool _move_down;
    bool _move_left;
    bool _move_up;
};
