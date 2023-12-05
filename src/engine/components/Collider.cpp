#include "Collider.h"

#include "../GameObject.h"
#include "../Scene.h"

Collider::Collider() {
    polygon.resize(4);
}

#include <iostream>
void Collider::regeneratePolygon() {
    polygon[0] = vec2{+transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    polygon[1] = vec2{+transform.scale.x / 2.0f, -transform.scale.y / 2.0f};    
    polygon[2] = vec2{-transform.scale.x / 2.0f, -transform.scale.y / 2.0f};
    polygon[3] = vec2{-transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    // rotate the diagonals to correspond with the objects rotation
    float rad = degToRad(transform.rotation);
    float cos = std::cos(rad), sin = std::sin(rad);
    for (size_t i = 0; i < 4; i++) {
        auto [x, y] = polygon[i];
        polygon[i] = transform.position + vec2{
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
        transform = obj->transform;
        regeneratePolygon();
    }

    // Check for collision with tilemap walls.
    std::shared_ptr<Scene> scene = obj->getScene();
    if (scene->hasTilemap()) {
        Tilemap& tilemap = scene->getTilemap();
        std::vector<Wall> const& walls = tilemap.getWalls();
        for (auto wall : walls) {
            Polygon wallLine{wall.line.ep1, wall.line.ep2};
            if (checkCollision_SAT(polygon, wallLine)) {
                std::cout << "SAT intersection!\n";
            }       
        }
    }
}