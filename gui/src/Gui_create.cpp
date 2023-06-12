/*
** EPITECH PROJECT, 2023
** gui
** File description:
** gui
*/

#include "Gui.hpp"
#include "logger.hpp"

// implement log

float perlin(float x, float y)
{
    int n = (int)x + (int)y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return (1.0f - (float)(t)*0.931322574615478515625e-9f);
}

// generate map _size_x x _size_y
// value between 0 and 9
void Gui::perlin_noise(void)
{
    int seed = rand() % 1000;
    float scale = 10.0f;
    int octaves = 61;
    float persistance = 0.5f;
    float lacunarity = 9.0f;

    for (int i = 0; i < _size_x; i++)
    {
        for (int j = 0; j < _size_y; j++)
        {
            float x = (float)i / _size_x * scale;
            float y = (float)j / _size_y * scale;

            float noise = 0.0f;
            float amplitude = 1.0f;
            float frequency = 1.0f;

            for (int k = 0; k < octaves; k++)
            {
                float sample_x = x * frequency + seed;
                float sample_y = y * frequency + seed;
                float perlin_value = (float)perlin(sample_x, sample_y) * 2.0f - 1.0f;
                noise += perlin_value * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            size_t value = (int)((noise + 1.0f) * 0.5f * 255.0f);
            std::cout << "value = " << value % 10 << std::endl;
            // if (i % 2 && !(j % 2))
            _map_decor[i][j] = 'a' + (value % 10);
        }
    }
}

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
    // perlin_noise();

    _zoom = 1.0f;

    _height_selected_tile = 0;
    _up_selected_tile = false;

    _shift_x = 0;
    _shift_y = 500;

    _speed_x = 0;
    _speed_y = 0;

    _selected_tile_x = 0;
    _selected_tile_y = 0;

    _move_right = false;
    _move_down = false;
    _move_left = false;
    _move_up = false;

    _eggs = std::vector<t_egg>();
    _font = sf::Font();
    _font.loadFromFile("gui/assets/font.ttf");
    _text = sf::Text("Hello World", _font);
}

Gui::~Gui()
{
}
