#include "Math.h"

#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef INFINITY
#define INFINITY 99999999
#endif

PointOrientation getPointOrientation(vec2 const& p, vec2 const& q, vec2 const& r) {
    float val = (q.y - p.y) * (r.x - q.x) - 
                (q.x - p.x) * (r.y - q.y);
    
    if (std::abs(val) < 0.01f)
        return ORIENTATION_COLLINEAR;
    
    return val > 0 ? ORIENTATION_CLOCKWISE : ORIENTATION_COUNTERCLOCKWISE; 
}

bool LineSegment::intersects(LineSegment const& other) const {
    PointOrientation o1 = getPointOrientation(ep1, ep2, other.ep1);
    PointOrientation o2 = getPointOrientation(ep1, ep2, other.ep2);
    PointOrientation o3 = getPointOrientation(other.ep1, other.ep2, ep1);
    PointOrientation o4 = getPointOrientation(other.ep1, other.ep2, ep2);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && onSegment(other.ep1)) return true; 
  
    if (o2 == 0 && onSegment(other.ep2)) return true; 
  
    if (o3 == 0 && other.onSegment(ep1)) return true; 
  
    if (o4 == 0 && other.onSegment(ep2)) return true; 

    return false;
}

bool LineSegment::onSegment(vec2 const& point) const {
    float lx = std::min(ep1.x, ep2.x), rx = std::max(ep1.x, ep2.x);
    float by = std::min(ep1.y, ep2.y), ty = std::max(ep1.y, ep2.y);
    return point.x >= lx && point.x <= rx && point.y >= by && point.y <= ty;
}

std::vector<vec2> getAxes(Polygon const& p) {
    std::vector<vec2> axes;
    for (size_t i = 0; i < p.size(); i++) {
        vec2 diff = p[(i + 1) % p.size()] - p[i];
        vec2 norm = {-diff.y, diff.x};
        axes.push_back(norm);
    }
    return axes;
}

bool checkCollision_SAT(Polygon const& p1, Polygon const& p2) {
    std::vector<vec2> p1Axes = getAxes(p1);
    std::vector<vec2> p2Axes = getAxes(p2);
    std::vector<vec2> axes = p1Axes;
    axes.insert(axes.end(), p2Axes.begin(), p2Axes.end());
    for (vec2 const& axis : axes) {
        float minP1 = INFINITY, maxP1 = -INFINITY;
        float minP2 = INFINITY, maxP2 = -INFINITY;
        // Perform projection of points onto the axis
        for (vec2 const& point : p1) {
            float projected = dot(axis, point);
            minP1 = std::min(minP1, projected);
            maxP1 = std::max(maxP1, projected);
        }
        for (vec2 const& point : p2) {
            float projected = dot(axis, point);
            minP2 = std::min(minP2, projected);
            maxP2 = std::max(maxP2, projected);
        }
        // Check for non overlap between the two projections
        if (maxP1 < minP2 || maxP2 < minP1) {
            return false;    
        }
    }
    return true;
}

float random(float a, float b) {
    float range = b - a;
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return a + r * range;
}

float degToRad(float degrees) {
    return degrees / 180.0f * M_PI;
}