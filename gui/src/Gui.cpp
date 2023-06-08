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

    _shift_x = 0;
    _shift_y = 500;

    _move_x = 0;
    _move_y = 0;

    _speed_up_x = false;
    _speed_up_y = false;
    _speed_down_x = false;
    _speed_down_y = false;
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

void Gui::draw_players(sf::RenderWindow &window)
{
    for (size_t i = 0; i < _players.size(); i++)
    {
        _sprites[ID_PLAYER].setPosition(_shift_x + _players[i].x * 64 + _players[i].y * 64, _shift_y + _players[i].y * 32 - _players[i].x * 32);
        // _sprites[ID_PLAYER].setRotation((_players[i].orientation - 1) * 90);
        _textures[ID_PLAYER].setSmooth(false);
        _sprites[ID_PLAYER].setTexture(_textures[ID_PLAYER]);
        // 22 px height
        // 16 px width
        _sprites[ID_PLAYER].setTextureRect(sf::IntRect(4 * 16, 1 * 22, 16, 22));
        window.draw(_sprites[ID_PLAYER]);
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

void Gui::draw_decor_map(sf::RenderWindow &window)
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
            _sprites[ID_TILE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32);
            window.draw(_sprites[ID_TILE]);
        }
    }
    // draw map resources
    for (int i = 0; i < _size_x; i++)
    {
        for (int j = _size_y - 1; j >= 0; j--)
        {
            if (_map[i][j].food > 0)
            {
                // food
                _sprites[ID_FOOD].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _textures[ID_FOOD].setSmooth(false);
                _sprites[ID_FOOD].setTexture(_textures[ID_FOOD]);
                _sprites[ID_FOOD].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
                window.draw(_sprites[ID_FOOD]);
            }
            if (_map[i][j].linemate > 0)
            {
                // green
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(1 * SIZE_STONE, 0 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
            }
            if (_map[i][j].deraumere > 0)
            {
                // purple
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(1 * SIZE_STONE, 1 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
            }
            if (_map[i][j].sibur > 0)
            {
                // blue
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(1 * SIZE_STONE, 3 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
            }
            if (_map[i][j].mendiane > 0)
            {
                // yellow
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(1 * SIZE_STONE, 2 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
            }
            if (_map[i][j].phiras > 0)
            {
                // red
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(12 * SIZE_STONE, 5 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
            }
            if (_map[i][j].thystame > 0)
            {
                // white
                _sprites[ID_STONE].setPosition(_shift_x + j * 64 + i * 64, _shift_y + i * 32 - j * 32 - 20);
                _sprites[ID_STONE].setTextureRect(sf::IntRect(2 * SIZE_STONE, 4 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[ID_STONE]);
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
    // _shift_x = 0;
    // _shift_y = 500;

    // bool _speed_up_x = false;
    // bool _speed_up_y = false;
    // bool _speed_down_x = false;
    // bool _speed_down_y = false;

    // _move_x = 0;
    // _move_y = 0;

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
            _speed_up_x = true;
        if (event.key.code == sf::Keyboard::Left)
            _speed_down_x = true;
        if (event.key.code == sf::Keyboard::Up)
            _speed_up_y = true;
        if (event.key.code == sf::Keyboard::Down)
            _speed_down_y = true;
    }
    else
    {
        _speed_up_x = false;
        _speed_down_x = false;
        _speed_up_y = false;
        _speed_down_y = false;
    }

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Right)
            _speed_up_x = false;
        if (event.key.code == sf::Keyboard::Left)
            _speed_down_x = false;
        if (event.key.code == sf::Keyboard::Up)
            _speed_up_y = false;
        if (event.key.code == sf::Keyboard::Down)
            _speed_down_y = false;
    }
    if (_speed_up_x)
    {
        if (_move_x >= SPEED_MAX)
            _move_x = SPEED_MAX;
        _move_x *= 1.1;
        _move_x += 1;
    }
    if (_speed_down_x)
    {
        if (_move_x <= -SPEED_MAX)
            _move_x = -SPEED_MAX;
        _move_x *= 1.1;
        _move_x -= 1;
    }
    if (_speed_up_y)
    {
        if (_move_y <= -SPEED_MAX)
            _move_y = -SPEED_MAX;
        _move_y *= 1.1;
        _move_y -= 1;
    }
    if (_speed_down_y)
    {
        if (_move_y >= SPEED_MAX)
            _move_y = SPEED_MAX;
        _move_y *= 1.1;
        _move_y += 1;
    }

    if (_move_x > 0 && !_speed_up_x)
    {
        _move_x *= 0.95;
        if (_move_x < 1)
            _move_x = 0;
    }
    if (_move_x < 0 && !_speed_down_x)
    {
        _move_x *= 0.95;
        if (_move_x > -1)
            _move_x = 0;
    }
    if (_move_y > 0 && !_speed_down_y)
    {
        _move_y *= 0.95;
        if (_move_y < 1)
            _move_y = 0;
    }
    if (_move_y < 0 && !_speed_up_y)
    {
        _move_y *= 0.95;
        if (_move_y > -1)
            _move_y = 0;
    }
    _shift_x += _move_x;
    _shift_y += _move_y;
}

void Gui::run(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    load_map();
    load_textures();

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        move_map(event);
        window.clear();
        // draw_map(window);
        draw_decor_map(window);
        draw_players(window);

        // window.draw(shape);
        window.display();
    }
    return;
}
