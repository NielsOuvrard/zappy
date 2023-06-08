/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

#define START_X 100
#define START_Y 500

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
        _sprites[8].setPosition(START_X + _players[i].x * 64 + _players[i].y * 64, START_Y + _players[i].y * 32 - _players[i].x * 32);
        _sprites[8].setRotation((_players[i].orientation - 1) * 90);
        _sprites[8].setTexture(_textures[8]);
        window.draw(_sprites[8]);
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
            _sprites[9].setTextureRect(sf::IntRect(x * 256, y * 256, 256, 256));
            // isometric
            _sprites[9].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32);
            window.draw(_sprites[9]);
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
                _sprites[11].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _textures[11].setSmooth(false);
                _sprites[11].setTexture(_textures[11]);
                _sprites[11].setTextureRect(sf::IntRect(2 * SIZE_FOOD, 1 * SIZE_FOOD, SIZE_FOOD, SIZE_FOOD));
                window.draw(_sprites[11]);
            }
            if (_map[i][j].linemate > 0)
            {
                // green
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(1 * SIZE_STONE, 0 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
            }
            if (_map[i][j].deraumere > 0)
            {
                // purple
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(1 * SIZE_STONE, 1 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
            }
            if (_map[i][j].sibur > 0)
            {
                // blue
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(1 * SIZE_STONE, 3 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
            }
            if (_map[i][j].mendiane > 0)
            {
                // yellow
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(1 * SIZE_STONE, 2 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
            }
            if (_map[i][j].phiras > 0)
            {
                // red
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(12 * SIZE_STONE, 5 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
            }
            if (_map[i][j].thystame > 0)
            {
                // white
                _sprites[10].setPosition(START_X + j * 64 + i * 64, START_Y + i * 32 - j * 32 - 20);
                _sprites[10].setTextureRect(sf::IntRect(2 * SIZE_STONE, 4 * SIZE_STONE, SIZE_STONE, SIZE_STONE));
                window.draw(_sprites[10]);
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

    _sprites[9].setTexture(_textures[9]);
    _sprites[9].setTextureRect(sf::IntRect(0, 0, 256, 256));
    _sprites[9].setScale(0.5, 0.5);

    _sprites[10].setTexture(_textures[10]);
    _sprites[10].setTextureRect(sf::IntRect(0, 0, SIZE_STONE, SIZE_STONE));
    _sprites[10].setScale(0.125, 0.125);

    _textures[11].setSmooth(false);
    _sprites[11].setTexture(_textures[11]);
    _sprites[11].setTextureRect(sf::IntRect(2, 1, SIZE_FOOD, SIZE_FOOD));
    // _sprites[11].setScale(1, 1);
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
        usleep(100000);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // else
            // {
            //     std::cout << "Event type: " << event.type << std::endl;
            // }
        }
        window.clear();
        // draw_map(window);
        draw_decor_map(window);
        draw_players(window);

        // window.draw(shape);
        window.display();
    }
    return;
}
