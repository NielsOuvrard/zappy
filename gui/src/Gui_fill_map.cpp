/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

// implement log

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
        // pfk (fork)
        // enw (egg)
        if (line.find("enw") != std::string::npos)
        {
            std::cout << LOG_GUI("creating egg");
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string player_id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            _eggs.push_back((t_egg){std::stoi(id), std::stoi(x), std::stoi(y), std::stoi(player_id)});
        }
        data = data.substr(data.find("\n") + 1);
    }
    return tna_found;
}
