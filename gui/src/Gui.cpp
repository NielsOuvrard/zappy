/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

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
            _players.push_back((t_player){std::stoi(id), std::stoi(x), std::stoi(y), std::stoi(orientation), std::stoi(level), team});
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
        _sprites[8].setPosition(_players[i].x * 64, _players[i].y * 64);
        _sprites[8].setRotation((_players[i].orientation - 1) * 90);
        _sprites[8].setTexture(_textures[8]);
        window.draw(_sprites[8]);
    }
}

void Gui::draw_map(sf::RenderWindow &window)
{
    for (int i = 0; i < _size_x; i++)
    {
        for (int j = 0; j < _size_y; j++)
        {
            _sprites[0].setPosition(i * 64, j * 64);
            _sprites[0].setTexture(_textures[0]);
            window.draw(_sprites[0]);
            if (_map[i][j].food > 0)
            {
                _sprites[1].setPosition(i * 64, j * 64);
                _sprites[1].setTexture(_textures[1]);
                window.draw(_sprites[1]);
            }
            if (_map[i][j].linemate > 0)
            {
                _sprites[2].setPosition(i * 64, j * 64);
                _sprites[2].setTexture(_textures[2]);
                window.draw(_sprites[2]);
            }
            if (_map[i][j].deraumere > 0)
            {
                _sprites[3].setPosition(i * 64, j * 64);
                _sprites[3].setTexture(_textures[3]);
                window.draw(_sprites[3]);
            }
            if (_map[i][j].sibur > 0)
            {
                _sprites[4].setPosition(i * 64, j * 64);
                _sprites[4].setTexture(_textures[4]);
                window.draw(_sprites[4]);
            }
            if (_map[i][j].mendiane > 0)
            {
                _sprites[5].setPosition(i * 64, j * 64);
                _sprites[5].setTexture(_textures[5]);
                window.draw(_sprites[5]);
            }
            if (_map[i][j].phiras > 0)
            {
                _sprites[6].setPosition(i * 64, j * 64);
                _sprites[6].setTexture(_textures[6]);
                window.draw(_sprites[6]);
            }
            if (_map[i][j].thystame > 0)
            {
                _sprites[7].setPosition(i * 64, j * 64);
                _sprites[7].setTexture(_textures[7]);
                window.draw(_sprites[7]);
            }
        }
    }
    return;
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
}

void Gui::run(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
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
        draw_map(window);
        draw_players(window);

        // window.draw(shape);
        window.display();
    }
    return;
}
