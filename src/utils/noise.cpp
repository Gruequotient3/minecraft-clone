#ifndef NOISE_CPP
#define NOISE_CPP

#include "noise.hpp"
#include "utilities.hpp"

float Noise::Noise2D(float x, float y){
    int n = x + y * 257;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) &
    0x7fffffff) / 1073741824.0f);
}

float Noise::Noise2D(glm::vec2& vect){
    int n = vect.x + vect.y * 257;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) &
    0x7fffffff) / 1073741824.0f);
}

float Noise::LerpNoise2D(float x, float y){
    float xi, yi;
    float xf, yf;
    float l00, l01, l10, l11;
    float l0, l1;

    xi = x >= 0 ? (int) x : (int) x - 1;
    xf = x - (float) xi;

    yi = y >= 0 ? (int) y : (int) y - 1;
    yf = y - (float) yi;

    l00 = Noise2D(xi, yi);
    l01 = Noise2D(xi+1, yi);
    l10 = Noise2D(xi, yi+1);
    l11 = Noise2D(xi+1, yi+1);

    l0 = Utils::Lerp(l00, l01, xf);
    l1 = Utils::Lerp(l10, l11, xf);

    return Utils::Lerp(l0, l1, yf);
}


float Noise::LerpNoise2D(glm::vec2& vect){
    float xi, yi;
    float xf, yf;
    float l00, l01, l10, l11;
    float l0, l1;

    xi = vect.x >= 0 ? (int) vect.x : (int) vect.x - 1;
    xf = vect.x - (float) xi;

    yi = vect.y >= 0 ? (int) vect.y : (int) vect.y - 1;
    yf = vect.y - (float) yi;

    l00 = Noise2D(xi, yi);
    l01 = Noise2D(xi+1, yi);
    l10 = Noise2D(xi, yi+1);
    l11 = Noise2D(xi+1, yi+1);

    l0 = Utils::Lerp(l00, l01, xf);
    l1 = Utils::Lerp(l10, l11, xf);

    return Utils::Lerp(l0, l1, yf);
}


float Noise::Noise3D(float x, float y, float z){
    int n = x + y * 257 + z * 757;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) &
    0x7fffffff) / 1073741824.0f);
}

float Noise::Noise3D(glm::vec3& vect){
    int n = vect.x + vect.y * 257 + vect.z * 757;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) &
    0x7fffffff) / 1073741824.0f);
}

float Noise::LerpNoise3D(float x, float y, float z){
    float xi, yi, zi;
    float xf, yf, zf;
    float l000, l001, l010, l011, l100, l101, l110, l111;
    float l00, l01, l10, l11;
    float l0, l1;

    xi = x >= 0 ? (int) x : (int) x - 1;
    xf = x - (float) xi;

    yi = y >= 0 ? (int) y : (int) y - 1;
    yf = y - (float) yi;

    zi = z >= 0 ? (int) z : (int) z - 1;
    zf = z - (float)zi;

    l000 = Noise3D(xi, yi, zi);
    l001 = Noise3D(xi+1, yi, zi);
    l010 = Noise3D(xi, yi+1, zi);
    l011 = Noise3D(xi+1, yi+1, zi);
    l100 = Noise3D(xi, yi, zi+1);
    l101 = Noise3D(xi+1, yi, zi+1);
    l110 = Noise3D(xi, yi+1, zi+1);
    l111 = Noise3D(xi+1, yi+1, zi+1);

    l00 = Utils::Lerp(l000, l001, xf);
    l01 = Utils::Lerp(l010, l011, xf);
    l10 = Utils::Lerp(l100, l101, xf);
    l11 = Utils::Lerp(l110, l111, xf);

    l0 = Utils::Lerp(l00, l01, yf);
    l1 = Utils::Lerp(l10, l11, yf);

    return Utils::Lerp(l0, l1, zf);
}

float Noise::LerpNoise3D(glm::vec3& vect){
    float xi, yi, zi;
    float xf, yf, zf;
    float l000, l001, l010, l011, l100, l101, l110, l111;
    float l00, l01, l10, l11;
    float l0, l1;

    xi = vect.x >= 0 ? (int) vect.x : (int) vect.x - 1;
    xf = vect.x - (float) xi;

    yi = vect.y >= 0 ? (int) vect.y : (int) vect.y - 1;
    yf = vect.y - (float) yi;

    zi = vect.z >= 0 ? (int) vect.z : (int) vect.z - 1;
    zf = vect.z - (float)zi;

    l000 = Noise3D(xi, yi, zi);
    l001 = Noise3D(xi+1, yi, zi);
    l010 = Noise3D(xi, yi+1, zi);
    l011 = Noise3D(xi+1, yi+1, zi);
    l100 = Noise3D(xi, yi, zi+1);
    l101 = Noise3D(xi+1, yi, zi+1);
    l110 = Noise3D(xi, yi+1, zi+1);
    l111 = Noise3D(xi+1, yi+1, zi+1);

    l00 = Utils::Lerp(l000, l001, xf);
    l01 = Utils::Lerp(l010, l011, xf);
    l10 = Utils::Lerp(l100, l101, xf);
    l11 = Utils::Lerp(l110, l111, xf);

    l0 = Utils::Lerp(l00, l01, yf);
    l1 = Utils::Lerp(l10, l11, yf);

    return Utils::Lerp(l0, l1, zf);
}


#endif