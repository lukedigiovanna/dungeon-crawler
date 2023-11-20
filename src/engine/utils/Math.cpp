#include "Math.h"

float random(float a, float b) {
    float range = b - a;
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return a + r * range;
}