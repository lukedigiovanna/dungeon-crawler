#pragma once

#include <utility>
#include <math.h>

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

struct vec2 {
    float x, y;
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

inline float dot(const vec2& lhs, const vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline float magnitude2(const vec2& vec) {
    return dot(vec, vec);
}

inline float magnitude(const vec2& vec) {
    return std::sqrt(magnitude2(vec));
}

// random numbers

float random(float a, float b);

float degToRad(float degrees);