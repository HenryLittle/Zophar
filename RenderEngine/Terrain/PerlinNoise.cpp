//
// Created by Henry Little on 2019/9/15.
//

#include <numeric>
#include <algorithm>
#include <random>
#include "PerlinNoise.hpp"

PerlinNoise::PerlinNoise(int seed) {
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    auto randomEngine = std::default_random_engine(seed);
    std::shuffle(p.begin(), p.end(), randomEngine);
    // duplicate the values
    p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::noise(double x, double y, double z) {
    int X = (int) std::floor(x) & 255,                  // FIND UNIT CUBE THAT
            Y = (int) std::floor(y) & 255,                  // CONTAINS POINT.
            Z = (int) std::floor(z) & 255;
    x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
    y -= std::floor(y);                                // OF POINT IN CUBE.
    z -= std::floor(z);
    double u = fade(x),                                // COMPUTE FADE CURVES
            v = fade(y),                                // FOR EACH OF X,Y,Z.
            w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,      // HASH COORDINATES OF
        B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;      // THE 8 CUBE CORNERS,

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),          // AND ADD
                                grad(p[BA], x - 1, y, z)),           // BLENDED
                           lerp(u, grad(p[AB], x, y - 1, z),      // RESULTS
                             grad(p[BB], x - 1, y - 1, z))),      // FROM  8
                lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),  // CORNERS
                             grad(p[BA + 1], x - 1, y, z - 1)),   // OF CUBE
                     lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                          grad(p[BB + 1], x - 1, y - 1, z - 1))));
}