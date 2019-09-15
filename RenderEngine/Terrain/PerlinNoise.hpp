//
// Created by Henry Little on 2019/9/15.
//

#ifndef RENDERENGINE_PERLINNOISE_HPP
#define RENDERENGINE_PERLINNOISE_HPP

#include <vector>

// reference https://cs.nyu.edu/~perlin/noise/ Java version written by Ken Perlin himself
class PerlinNoise {
    // permutation vector
    std::vector<int> p;
public:
    PerlinNoise(int seed);
    double noise(double x, double y, double z);
private:
    // linear interplation
    static double lerp(double t, double a, double b) {
        return a + t * (b - a);
    };

    static double fade(double t) {
        return t * t * t * (t * (t * 6 -15) + 10);
    };

    static double grad(int hash, double x, double y, double z) {
        int h = hash & 0xF;
        double u = h < 0x8 ? x : y;
        double v = h < 0x4 ? y : (h == 0xC || h == 0xE ? x : z);
        return ((h & 0x1) == 0 ? u : -u) + ((h & 0x2) == 0 ? v : -v);
    };
};


#endif //RENDERENGINE_PERLINNOISE_HPP
