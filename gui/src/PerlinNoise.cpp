/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-kenan.blasius
** File description:
** raytracer
*/

#include "PerlinNoise.hpp"

Perlin &Perlin::getInstance(int size_x, int size_y)
{
    static Perlin instance(size_x, size_y);
    return instance;
}

float Perlin::get_color(float u, float v)
{
    int i = (int)(u * width);
    int j = (int)(v * height);
    return Image[i + j * width].x;
}

Perlin::Perlin(int size_x, int size_y)
{
    srand(time(NULL));
    width = size_x;
    height = size_y;
    _frequency = 2;
    _octaves = 64;
    // generate Perlin noise image in 2D and store it in Image
    Image = std::vector<Vec3f>(width * height);

    reseed(rand());

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float fx = width / _frequency;
            float fy = height / _frequency;

            float result = accumulatedNoise2D(x / fx, y / fy, _octaves, 2.0f, 0.25f);

            Image[x + y * width] = Vec3f(result, result, result);
        }
    }
    // // write image to file for debugging
    // std::ofstream file("noise.ppm");
    // file << "P3\n"
    //      << width << " " << height << "\n255\n";
    // for (int i = 0; i < width * height; i++)
    // {
    //     file << (int)(Image[i].x * 255) << " " << (int)(Image[i].y * 255) << " " << (int)(Image[i].z * 255) << "\n";
    // }
    // file.close();
}

// reseed the class
void Perlin::reseed(unsigned int _seed)
{
    seed = _seed;

    // populate permutation table in order
    for (unsigned int i = 0; i < 256; i++)
    {
        p[i] = i;
    }

    // shuffle
    std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

    // duplicate array for overflow
    for (unsigned int i = 0; i < 256; i++)
    {
        p[256 + i] = p[i];
    }
}

// 2D Perlin Noise
float Perlin::noise2D(float x, float y)
{
    // find smallest point of square containing target
    int xi = (int)(floor(x)) & 255;
    int yi = (int)(floor(y)) & 255;

    // get decimal value of each component
    x -= floor(x);
    y -= floor(y);

    // get smooth value from fade function (becomes weight for each dimension)
    float sx = fade(x);
    float sy = fade(y);

    // get hash value for all neighboring points
    unsigned char aa, ab, ba, bb;
    aa = p[p[xi] + yi];
    ab = p[p[xi] + yi + 1];
    ba = p[p[xi + 1] + yi];
    bb = p[p[xi + 1] + yi + 1];

    // get weighted average
    float avg = lerp(
        sy,
        lerp( // "top"
            sx,
            grad(aa, x, y, 0),
            grad(ba, x - 1, y, 0)),
        lerp( // "bottom"
            sx,
            grad(ab, x, y - 1, 0),
            grad(bb, x - 1, y - 1, 0)));

    // return avg mapped from [-1, 1] (theoretically) to [0, 1]
    return map(avg, -1, 1, 0, 1);
}

// 2D accumulated noise
float Perlin::accumulatedNoise2D(float x, float y, int octaves, float lacunarity, float gain)
{
    float result = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float maxVal = 0.0f; // used to normalize result

    for (; octaves > 0; octaves--)
    {
        result += noise2D(x * frequency, y * frequency) * amplitude;

        maxVal += amplitude;

        amplitude *= gain;
        frequency *= lacunarity;
    }

    // return normalized result
    return result / maxVal;
}

// fade function: f(t) = 6*t^5 - 15*t^4 + 10*t^3 (optimize for fewer multiplications)
float Perlin::fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// linear interpolation
float Perlin::lerp(float t, float a, float b)
{
    return a + t * (b - a);
}

// map function
float Perlin::map(float val, float ogMin, float ogMax, float newMin, float newMax)
{
    // get proportion in original range
    float prop = (val - ogMin) / (ogMax - ogMin);

    return lerp(prop, newMin, newMax);
}

// gradient function
// calculate the dot product between the gradient vector and distance vector
float Perlin::grad(unsigned char hash, float x, float y, float z)
{
    // convert the last 4 bits of the hash into one of 12 possible gradients
    int h = hash & 0b1111; // = hash & 15 = hash % 16 = get last 4 bits

    // if first bit 1, set to x, otherwise set to y
    float u = h < 0b1000 ? x : y;

    // if first/second bits 0, set to y
    // if first/second bits 1, set to x
    // else set to z
    float v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x
                                                          : z;

    // make u, v negative based on the last 2 bits, then add results
    // adding results is like dot product because gradient components are 1,
    // so results of dot product is adding distance components
    return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);
}
