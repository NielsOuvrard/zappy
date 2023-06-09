/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define ID_TILE 9
#define ID_STONE 10
#define ID_FOOD 11
#define ID_PLAYER 12

#define SIZE_TILE 64
#define SIZE_STONE 512
#define SIZE_FOOD 32

// implement log

Gui::Gui(std::string data)
{
    bool size_found = false;
    while (std::string::npos != data.find("\n") && !size_found)
    {
        std::string line = data.substr(0, data.find("\n"));
        // std::cout << "- " << line << std::endl;
        if (line.find("msz") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            std::string y = values.substr(values.find(" ") + 1);
            _size_x = std::stoi(x);
            _size_y = std::stoi(y);
            _map = new t_tile *[_size_x];
            for (int i = 0; i < _size_x; i++)
            {
                _map[i] = new t_tile[_size_y];
                for (int j = 0; j < _size_y; j++)
                {
                    _map[i][j] = (t_tile){0, 0, 0, 0, 0, 0, 0};
                }
            }
            size_found = true;
        }
    }

    _zoom = 1.0f;

    _shift_x = 0;
    _shift_y = 500;

    _speed_x = 0;
    _speed_y = 0;

    _move_right = false;
    _move_up = false;
    _move_left = false;
    _move_down = false;
}

Gui::~Gui()
{
}

bool Gui::fill_map(std::string data)
{
    bool tna_found = false;
    while (std::string::npos != data.find("\n"))
    {
        std::string line = data.substr(0, data.find("\n"));
        std::cout << LOG_GUI(line);
        if (line.find("sgt") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            _freq = std::stoi(values);
        }
        if (line.find("tna") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            _teams.push_back(values);
            tna_found = true;
        }
        if (line.find("bct") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string food = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string linemate = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string deraumere = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string sibur = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string mendiane = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string phiras = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string thystame = values.substr(0, values.find(" "));
            _map[std::stoi(x)][std::stoi(y)] = (t_tile){
                std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame)};
        }
        if (line.find("pnw") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string orientation = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string level = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string team = values.substr(0, values.find(" "));
            _players.push_back((t_player){std::stoi(id), std::stoi(x) - 1, std::stoi(y) - 1, std::stoi(orientation), std::stoi(level), team});
        }
        if (line.find("pdi") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    _players.erase(_players.begin() + i);
                    break;
                }
            }
        }
        // ppo
        if (line.find("ppo") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string orientation = values.substr(0, values.find(" "));
            for (int i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    _players[i].x = std::stoi(x);
                    _players[i].y = std::stoi(y);
                    _players[i].orientation = std::stoi(orientation);
                    break;
                }
            }
        }
        data = data.substr(data.find("\n") + 1);
    }
    return tna_found;
}

#define SIZE_PLAYER_X 16
#define SIZE_PLAYER_Y 22

void Gui::draw_players()
{
    for (size_t i = 0; i < _players.size(); i++)
    {
        _sprites[ID_PLAYER].setPosition(
            (_shift_x + _players[i].x * 64 + _players[i].y * 64 + 32) * _zoom,
            (_shift_y + _players[i].y * 32 - _players[i].x * 32 - 32) * _zoom);
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

    while (std::getline(ifs, line))
    {
        _map_decor.push_back(line);
        std::cout << LOG_GUI(line);
    }
}

float Gui::draw_stone(int i, int j, int pos_x, int pos_y)
{
    _sprites[ID_STONE].setPosition((_shift_x + j * 64 + i * 64 + 32) * _zoom, (_shift_y + i * 32 - j * 32 - 32) * _zoom);
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
            // isometric
            _sprites[ID_TILE].setPosition((_shift_x + j * 64 + i * 64) * _zoom, (_shift_y + i * 32 - j * 32) * _zoom);
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
            if (_map[i][j].linemate > 0)
                draw_stone(i, j, 1, 0);
            if (_map[i][j].deraumere > 0)
                draw_stone(i, j, 1, 1);
            if (_map[i][j].sibur > 0)
                draw_stone(i, j, 1, 3);
            if (_map[i][j].mendiane > 0)
                draw_stone(i, j, 1, 2);
            if (_map[i][j].phiras > 0)
                draw_stone(i, j, 12, 5);
            if (_map[i][j].thystame > 0)
                draw_stone(i, j, 2, 4);
            if (_map[i][j].food > 0)
            {
                // food
                _sprites[ID_FOOD].setPosition((_shift_x + j * 64 + i * 64 + 32) * _zoom, (_shift_y + i * 32 - j * 32 + 16) * _zoom);
                _textures[ID_FOOD].setSmooth(false);
                _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
                _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
                _sprites[ID_FOOD].setScale(_zoom, _zoom);
                _window->draw(_sprites[ID_FOOD]);
            }
        }
    }
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
    _sprites[8].setOrigin(32, 32);

    _sprites[ID_TILE].setTexture(_textures[ID_TILE]);
    _sprites[ID_TILE].setTextureRect(sf::IntRect(0, 0, 256, 256));
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
}

#define SPEED_MAX 15

void Gui::move_map(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left)
            _move_right = true;
        if (event.key.code == sf::Keyboard::Right)
            _move_left = true;
        if (event.key.code == sf::Keyboard::Down)
            _move_down = true;
        if (event.key.code == sf::Keyboard::Up)
            _move_up = true;
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left)
            _move_right = false;
        if (event.key.code == sf::Keyboard::Right)
            _move_left = false;
        if (event.key.code == sf::Keyboard::Down)
            _move_down = false;
        if (event.key.code == sf::Keyboard::Up)
            _move_up = false;
    }
    if (_move_right)
    {
        _speed_x *= 1.1;
        _speed_x += 1;
        if (_speed_x >= SPEED_MAX)
            _speed_x = SPEED_MAX;
    }
    if (_move_left)
    {
        _speed_x *= 1.1;
        _speed_x -= 1;
        if (_speed_x <= -SPEED_MAX)
            _speed_x = -SPEED_MAX;
    }
    if (_move_up)
    {
        _speed_y *= 1.1;
        _speed_y -= 1;
        if (_speed_y <= -SPEED_MAX)
            _speed_y = -SPEED_MAX;
    }
    if (_move_down)
    {
        _speed_y *= 1.1;
        _speed_y += 1;
        if (_speed_y >= SPEED_MAX)
            _speed_y = SPEED_MAX;
    }

    if (_speed_x > 0 && !_move_right)
    {
        _speed_x *= 0.95;
        if (_speed_x < 1)
            _speed_x = 0;
    }
    if (_speed_x < 0 && !_move_left)
    {
        _speed_x *= 0.95;
        if (_speed_x > -1)
            _speed_x = 0;
    }
    if (_speed_y > 0 && !_move_down)
    {
        _speed_y *= 0.95;
        if (_speed_y < 1)
            _speed_y = 0;
    }
    if (_speed_y < 0 && !_move_up)
    {
        _speed_y *= 0.95;
        if (_speed_y > -1)
            _speed_y = 0;
    }
    _shift_x -= _speed_x;
    _shift_y += _speed_y;
}

void Gui::run(void)
{
    sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
    _window = &win;
    load_map();
    load_textures();

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    _window->setFramerateLimit(60);
    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                _window->setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                {
                    _zoom *= 1.1;
                    _shift_x *= 1.1;
                    _shift_y *= 1.1;
                }
                if (event.key.code == sf::Keyboard::M)
                {
                    _zoom /= 1.1;
                    _shift_x /= 1.1;
                    _shift_y /= 1.1;
                }
            }
        }
        move_map(event);
        _window->clear();
        // draw_map(_window);
        draw_decor_map();
        draw_players();

        // _window->draw(shape);
        _window->display();
    }
    return;
}
