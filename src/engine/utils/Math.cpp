#include "Math.h"

#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef INFINITY
#define INFINITY 99999999
#endif

math::vec2 math::vec2::normalized() const {
    return *this / magnitude();
}

float math::vec2::magnitude2() const {
    return dot(*this, *this);
}

float math::vec2::magnitude() const {
    return std::sqrt(magnitude2());
}

math::PointOrientation math::getPointOrientation(math::vec2 const& p, math::vec2 const& q, math::vec2 const& r) {
    float val = (q.y - p.y) * (r.x - q.x) - 
                (q.x - p.x) * (r.y - q.y);
    
    if (std::abs(val) < 0.01f)
        return math::ORIENTATION_COLLINEAR;
    
    return val > 0 ? math::ORIENTATION_CLOCKWISE : math::ORIENTATION_COUNTERCLOCKWISE; 
}

bool math::LineSegment::intersects(LineSegment const& other) const {
    math::PointOrientation o1 = math::getPointOrientation(ep1, ep2, other.ep1);
    math::PointOrientation o2 = math::getPointOrientation(ep1, ep2, other.ep2);
    math::PointOrientation o3 = math::getPointOrientation(other.ep1, other.ep2, ep1);
    math::PointOrientation o4 = math::getPointOrientation(other.ep1, other.ep2, ep2);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && onSegment(other.ep1)) return true; 
  
    if (o2 == 0 && onSegment(other.ep2)) return true; 
  
    if (o3 == 0 && other.onSegment(ep1)) return true; 
  
    if (o4 == 0 && other.onSegment(ep2)) return true; 

    return false;
}

bool math::LineSegment::onSegment(vec2 const& point) const {
    float lx = std::min(ep1.x, ep2.x), rx = std::max(ep1.x, ep2.x);
    float by = std::min(ep1.y, ep2.y), ty = std::max(ep1.y, ep2.y);
    return point.x >= lx && point.x <= rx && point.y >= by && point.y <= ty;
}

std::vector<math::vec2> math::getAxes(math::Polygon const& p) {
    std::vector<math::vec2> axes;
    int k = p.points.size() > 2 ? p.points.size() : 1;
    for (size_t i = 0; i < k; i++) {
        math::vec2 diff = p.points[(i + 1) % p.points.size()] - p.points[i];
        math::vec2 norm = {-diff.y, diff.x};
        axes.push_back(norm.normalized());
    }
    return axes;
}

#include <iostream>
math::SATResult math::checkCollision_SAT(math::Polygon const& p1, math::Polygon const& p2) {
    std::vector<math::vec2> p1Axes = getAxes(p1);
    std::vector<math::vec2> p2Axes = getAxes(p2);
    std::vector<math::vec2> axes = p1Axes;
    axes.insert(axes.end(), p2Axes.begin(), p2Axes.end());

    float overlap = INFINITY;
    math::vec2 overlapAxis{0, 0};

    for (math::vec2 const& axis : axes) {
        float minP1 = INFINITY, maxP1 = -INFINITY;
        float minP2 = INFINITY, maxP2 = -INFINITY;
        // Perform projection of points onto the axis
        for (math::vec2 const& point : p1.points) {
            float projected = math::dot(axis, point);
            minP1 = std::min(minP1, projected);
            maxP1 = std::max(maxP1, projected);
        }
        for (math::vec2 const& point : p2.points) {
            float projected = math::dot(axis, point);
            minP2 = std::min(minP2, projected);
            maxP2 = std::max(maxP2, projected);
        }

        // Check for non overlap between the two projections
        if (maxP1 < minP2 || maxP2 < minP1) {
            return {false, 0, {0, 0}};    
        }

        float thisOverlap;
        if (std::abs(minP2 - maxP2) < 0.001f) {
            thisOverlap = std::min(maxP2 - minP1, maxP1 - maxP2);
        }
        else {
            thisOverlap = std::min(maxP1, maxP2) - std::max(minP1, minP2);
        }
        if (thisOverlap < overlap) {
            overlap = thisOverlap;
            overlapAxis = axis;
        }
    }

    return {true, overlap, overlapAxis};
}

unsigned hash(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

math::vec2 randomGradient(int ix, int iy, unsigned seed=6482) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    // unsigned a = hash(ix + seed), b = hash(iy + hash(seed));
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    math::vec2 v{std::cos(random), v.y = std::sin(random)};
    return v;
}

float dotGridGradient(int ix, int iy, float x, float y, unsigned seed=53842) {
    math::vec2 gradient = randomGradient(ix, iy, seed);
    math::vec2 d{x - static_cast<float>(ix), y - static_cast<float>(iy)};
    return dot(d, gradient);
}

math::PerlinNoise::PerlinNoise() : PerlinNoise(1) {

}

math::PerlinNoise::PerlinNoise(unsigned seed) : seed(seed) {

}

float math::PerlinNoise::get(float x, float y) const {
    int x0 = static_cast<int>(x), x1 = x0 + 1;
    int y0 = static_cast<int>(y), y1 = y0 + 1;

    float sx = x - static_cast<float>(x0);
    float sy = y - static_cast<float>(y0);

    float n0, n1;
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);

    float ix0 = math::interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    
    float ix1 = math::interpolate(n0, n1, sx);

    return math::interpolate(ix0, ix1, sy);
}

float math::random(float a, float b) {
    float range = b - a;
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return a + r * range;
}

float math::interpolate(float a0, float a1, float w) {
    return (a1 - a0) * w;
}

float math::degToRad(float degrees) {
    return degrees / 180.0f * M_PI;
}