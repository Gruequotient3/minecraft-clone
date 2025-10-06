#ifndef NOISE_HPP
#define NOISE_HPP

#include <glm/glm.hpp>

struct NoiseSettings{
    float strength;
    int octave;
    float amplitude;
    float frequency;
    float persistence;
    float lacunarity;
};

namespace Noise{
    float Noise2D(float x, float y);
    float Noise2D(glm::vec2& vect);
    float LerpNoise2D(float x, float y);
    float LerpNoise2D(glm::vec2& vect);

    float Noise3D(float x, float y, float z);
    float Noise3D(glm::vec3& vect);
    float LerpNoise3D(float x, float y, float z);
    float LerpNoise3D(glm::vec3& vect);
}


#endif