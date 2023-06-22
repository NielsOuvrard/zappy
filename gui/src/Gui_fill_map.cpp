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
            _slider_value = _freq / 10;
            _slider_value = _slider_value < 1 ? 1 : _slider_value;
            _slider_value = _slider_value > 100 ? 100 : _slider_value;
        }
        else if (line.find("tna") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            _teams.push_back(values);
            tna_found = true;
        }
        else if (line.find("bct") != std::string::npos)
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
            _map[std::stoi(y)][std::stoi(x)] = (t_tile){
                {std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame)},
                _map[std::stoi(y)][std::stoi(x)].is_incanting};
        }
        // data player
        else if (line.find("pnw") != std::string::npos)
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
            int team_index = 0;
            for (int i = 0; _teams.size() > 0 && i < _teams.size(); i++)
            {
                if (_teams[i] == team)
                {
                    team_index = i;
                    break;
                }
            }
            t_player data = {
                std::stoi(id),
                std::stoi(x),
                std::stoi(y),
                std::stoi(orientation),
                std::stoi(level),
                team_index,
                {0, 0, 0, 0, 0, 0, 0},
                false};
            _players.push_back(data);
        }
        else if (line.find("pdi") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    _players.erase(_players.begin() + i);
                    if (_selected_player == i)
                        _selected_player = 0;
                    break;
                }
            }
        }
        // ppo
        else if (line.find("ppo") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string orientation = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
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
        // enw (egg)
        else if (line.find("enw") != std::string::npos)
        {
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
        else if (line.find("pgt") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string resource = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    _players[i].inventory[std::stoi(resource)]++;
                }
            }
        }
        // pic (incantation)
        else if (line.find("pic") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string level = values.substr(0, values.find(" "));
            std::vector<int> players;
            while (values.find(" ") != std::string::npos)
            {
                values = values.substr(values.find(" ") + 1);
                players.push_back(std::stoi(values.substr(0, values.find(" "))));
            }
            _list_incants.push_back((t_incant){players, std::stoi(level), std::stoi(x), std::stoi(y)});
            for (size_t i = 0; i < _players.size(); i++)
            {
                for (size_t j = 0; j < players.size(); j++)
                {
                    if (_players[i].id == players[j])
                    {
                        _players[i].is_incanting = true;
                    }
                }
            }
            std::cout << "Incantation started at " << x << " " << y << " level " << level << std::endl;
            _map[std::stoi(y)][std::stoi(x)].is_incanting = std::stoi(level);
        }
        // pie (incantation end)
        else if (line.find("pie") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string result = values.substr(0, values.find(" "));
            // result = 1 when incantation success
            // result = 0 when incantation fail
            if (_map[std::stoi(y)][std::stoi(x)].is_incanting == 0)
                std::cout << LOG_ERR_GUI("!!! Incantation already stopped at " << x << " " << y);
            _map[std::stoi(y)][std::stoi(x)].is_incanting = 0;

            // for each incantation
            for (size_t i_incant = 0; i_incant < _list_incants.size(); i_incant++)
            {
                if (_list_incants[i_incant].x == std::stoi(x) && _list_incants[i_incant].y == std::stoi(y))
                {
                    // for each id_player in incantation
                    for (size_t i_pla_inc = 0; i_pla_inc < _list_incants[i_incant].players.size(); i_pla_inc++)
                    {
                        // for each player
                        for (size_t i_pla = 0; i_pla < _players.size(); i_pla++)
                        {
                            if (_players[i_pla].id == _list_incants[i_incant].players[i_pla_inc])
                            {
                                _players[i_pla].is_incanting = false;
                                if (result == "1")
                                {
                                    _players[i_pla].level++;
                                }
                            }
                        }
                    }
                    _list_incants.erase(_list_incants.begin() + i_incant);
                    break;
                }
            }
        }
        // pfk (fork)
        else if (line.find("pfk") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    // fork
                }
            }
        }
        // broadcast
        else if (line.find("bpc") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    // broadcast
                }
            }
        }
        // pic (incantation)
        else if (line.find("pic") != std::string::npos)
        {
            std::string values = line.substr(line.find(" ") + 1);
            std::string x = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string y = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string level = values.substr(0, values.find(" "));
            values = values.substr(values.find(" ") + 1);
            std::string id = values.substr(0, values.find(" "));
            for (size_t i = 0; i < _players.size(); i++)
            {
                if (_players[i].id == std::stoi(id))
                {
                    // incantation
                }
            }
        }
        else if (line.find("sbp") != std::string::npos)
        {
            std::cout << LOG_GUI("Command success");
        }
        else if (line.find("suc") != std::string::npos)
        {
            std::cout << LOG_ERR_GUI("Command failed");
        }
        else
        {
            std::cout << LOG_ERR_GUI("Unknown command: " << line);
        }

        data = data.substr(data.find("\n") + 1);
    }
    return tna_found;
}
