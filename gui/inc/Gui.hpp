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
    void draw_players(void);
    void load_textures(void);
    void load_map(void);
    void draw_decor_map(void);
    void move_map(sf::Event event);
    void interface(void);

    float draw_stone(int i, int j, int pos_x, int pos_y);

    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Texture> _textures;

    t_tile **_map;
    std::vector<std::string> _map_decor;
    std::vector<std::string> _teams;
    std::vector<t_player> _players;

    // eggs
    std::vector<t_egg> _eggs;

    sf::RenderWindow *_window;
    std::string _ressources[7] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

    sf::Font _font;
    sf::Text _text;

    size_t _selected_tile_x;
    size_t _selected_tile_y;

    float _zoom;

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
