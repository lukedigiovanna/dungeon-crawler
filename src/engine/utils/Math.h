#pragma once

#include <utility>
#include <math.h>
#include <vector>

// An exercise in over-engineering :-)

// template <typename T>
// struct vec2 {
//     T x, y;
// };

// template<typename T1, typename T2>
// auto operator+(const vec2<T1>& lhs, const vec2<T2>& rhs)
// -> vec2<decltype(std::declval<T1>() + std::declval<T2>())> {
//     return {lhs.x + rhs.x, lhs.y + rhs.y};
// }

// template<typename T1, typename T2>
// auto operator*(const vec2<T1>& lhs, const vec2<T2>& rhs)
// -> decltype(std::declval<T1>() * std::declval<T2>()) {
//     return lhs.x * rhs.x + lhs.y * rhs.y;
// }

// A more practical solution:

namespace math {
struct vec2 {
    float x, y;

    vec2 normalized() const;
    float magnitude2() const;
    float magnitude() const;
};

inline vec2 operator+(const vec2& lhs, const vec2& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y};
}

inline void operator+=(vec2& lhs, const vec2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}


inline vec2 operator-(const vec2& lhs, const vec2& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y};
}

inline void operator-=(vec2& lhs, const vec2& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
}

inline vec2 operator*(const vec2& lhs, float rhs) {
    return { lhs.x * rhs, lhs.y * rhs};
}

inline void operator*=(vec2& lhs, float rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
}

inline vec2 operator*(const vec2& lhs, const vec2& rhs) {
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}

inline void operator*=(vec2& lhs, const vec2& rhs) {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
}

inline vec2 operator/(const vec2& lhs, float rhs) {
    return { lhs.x / rhs, lhs.y / rhs};
}

inline void operator/=(vec2& lhs, float rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
}

inline vec2 operator/(const vec2& lhs, const vec2& rhs) {
    return { lhs.x / rhs.x, lhs.y / rhs.y };
}

inline void operator/=(vec2& lhs, const vec2& rhs) {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
}

inline bool operator!=(vec2 const& lhs, vec2 const& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

inline bool operator==(vec2 const& lhs, vec2 const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline float dot(const vec2& lhs, const vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

struct Transform {
    vec2 position;
    vec2 scale;
    float rotation;
};

inline bool operator==(Transform const& lhs, Transform const& rhs) {
    return lhs.position == rhs.position && lhs.scale == rhs.scale && lhs.rotation == rhs.rotation;
}

inline bool operator!=(Transform const& lhs, Transform const& rhs) {
    return lhs.position != rhs.position || lhs.scale != rhs.scale || lhs.rotation != rhs.rotation;
}

enum PointOrientation {
    ORIENTATION_COLLINEAR,
    ORIENTATION_CLOCKWISE,
    ORIENTATION_COUNTERCLOCKWISE
};

PointOrientation getPointOrientation(vec2 const& p, vec2 const& q, vec2 const& r);

struct LineSegment {
    vec2 ep1, ep2;

    // Checks if the given line segment intersects with this
    bool intersects(LineSegment const& other) const;

private:
    // Given they are collinear, checks if the point is on this line segment
    bool onSegment(vec2 const& point) const;
};

struct Polygon {
    std::vector<vec2> points;
    vec2 center;
};

struct SATResult {
    bool collided;
    float overlap; // Minimum amount of overlap determined, useful for resolving static collisions.
    vec2 overlapAxis;
};

std::vector<vec2> getAxes(Polygon const& p);

SATResult checkCollision_SAT(Polygon const& p1, Polygon const& p2);

// random numbers

float random(float a, float b);

float degToRad(float degrees);
}