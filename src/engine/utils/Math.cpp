#include "Math.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float random(float a, float b) {
    float range = b - a;
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return a + r * range;
}

float degToRad(float degrees) {
    return degrees / 180.0f * M_PI;
}