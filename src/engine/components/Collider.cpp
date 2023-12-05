#include "Collider.h"

#include "../GameObject.h"
#include "../Scene.h"

Collider::Collider() {
    polygon.resize(4);
}

#include <iostream>
void Collider::regeneratePolygon() {
    std::shared_ptr<GameObject> obj = getGameObject();
    transform = obj->transform;

    polygon[0] = math::vec2{+transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    polygon[1] = math::vec2{+transform.scale.x / 2.0f, -transform.scale.y / 2.0f};    
    polygon[2] = math::vec2{-transform.scale.x / 2.0f, -transform.scale.y / 2.0f};
    polygon[3] = math::vec2{-transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    // rotate the diagonals to correspond with the objects rotation
    float rad = math::degToRad(transform.rotation);
    float cos = std::cos(rad), sin = std::sin(rad);
    for (size_t i = 0; i < 4; i++) {
        auto [x, y] = polygon[i];
        polygon[i] = transform.position + math::vec2{
            x * cos - y * sin,
            x * sin + y * cos
        };
    }
    std::cout << transform.position.x << ", " << transform.position.y << 
        "\n\t x " << polygon[0].x << ", " << polygon[0].y << 
        "\n\t x " << polygon[1].x << ", " << polygon[1].y << 
        "\n\t x " << polygon[2].x << ", " << polygon[2].y <<
        "\n\t x " << polygon[3].x << ", " << polygon[3].y << std::endl;
}

void Collider::init() {
    regeneratePolygon();
}

void Collider::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    if (obj->transform != transform) {
        regeneratePolygon();
    }

    // Check for collision with tilemap walls.
    std::shared_ptr<Scene> scene = obj->getScene();
    if (scene->hasTilemap()) {
        Tilemap& tilemap = scene->getTilemap();
        float scale = tilemap.getScale();
        std::vector<math::Polygon> const& walls = tilemap.getWallPolygons();
        for (auto wall : walls) {
            math::SATResult result = checkCollision_SAT(polygon, wall);
            if (result.collided) {
                // vec2 wallPos{wall[0].x + scale / 2.0f, wall[0].y - scale / 2.0f};
                // vec2 d = (obj->transform.position - wallPos).normalized();
                math::vec2 d = result.overlapAxis.normalized();
                math::vec2 correction = d * result.overlap;
                obj->transform.position += correction;
                regeneratePolygon();
                std::cout << result.overlap << "\n";
            }
        }
    }
}