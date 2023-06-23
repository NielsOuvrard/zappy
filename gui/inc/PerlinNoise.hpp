/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-kenan.blasius
** File description:
** raytracer
*/

#pragma once
#include "vector.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <filesystem>
#include <fstream>

// class to generate perlin noise in 2D
class Perlin
{
    std::vector<Vec3f> Image;
    int width, height;
    unsigned int seed;
    unsigned char p[512];
    float _frequency;
    int _octaves;

public:
    static Perlin &getInstance(int size_x, int size_y);

    float get_color(float u, float v);

    Perlin(int size_x, int size_y);

    // reseed the class
    void reseed(unsigned int _seed);

    // 2D Perlin Noise
    float noise2D(float x, float y);

    // 2D accumulated noise
    float accumulatedNoise2D(float x, float y, int octaves = 8, float lacunarity = 2.0f, float gain = 0.5f);

private:
    // fade function: f(t) = 6*t^5 - 15*t^4 + 10*t^3 (optimize for fewer multiplications)
    float fade(float t);

    // linear interpolation
    float lerp(float t, float a, float b);

    // map function
    float map(float val, float ogMin, float ogMax, float newMin, float newMax);

    // gradient function
    // calculate the dot product between the gradient vector and distance vector
    float grad(unsigned char hash, float x, float y, float z);
};
