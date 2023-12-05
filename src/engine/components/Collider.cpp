#include "Collider.h"

#include "../GameObject.h"
#include "../Scene.h"

Collider::Collider() {

}

#include <iostream>
void Collider::regenerateDiagonals() {
    std::array<vec2, 4> corners;
    corners[0] = vec2{diagScale.x / 2.0f, diagScale.y / 2.0f};
    corners[1] = vec2{diagScale.x / 2.0f, -diagScale.y / 2.0f};    
    corners[2] = vec2{-diagScale.x / 2.0f, diagScale.y / 2.0f};
    corners[3] = vec2{-diagScale.x / 2.0f, -diagScale.y / 2.0f};
    // rotate the diagonals to correspond with the objects rotation
    float rad = degToRad(diagRotation);
    float cos = std::cos(rad), sin = std::sin(rad);
    for (size_t i = 0; i < 4; i++) {
        auto [x, y] = corners[i];
        diagonals[i].ep1 = diagPos;
        diagonals[i].ep2 = diagPos + vec2{
            x * cos - y * sin,
            x * sin + y * cos
        };
    }
    std::cout << diagonals[0].ep1.x << ", " << diagonals[0].ep1.y << 
        "\n\t x " << diagonals[0].ep2.x << ", " << diagonals[0].ep2.y << 
        "\n\t x " << diagonals[1].ep2.x << ", " << diagonals[1].ep2.y << 
        "\n\t x " << diagonals[2].ep2.x << ", " << diagonals[2].ep2.y <<
        "\n\t x " << diagonals[3].ep2.x << ", " << diagonals[3].ep2.y << std::endl;
}

void Collider::init() {
    regenerateDiagonals();
}

void Collider::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    if (obj->position != diagPos || obj->rotation != diagRotation || obj->scale != diagScale) {
        diagPos = obj->position;
        diagRotation = obj->rotation;
        diagScale = obj->scale;
        regenerateDiagonals();
    }

    // Check for collision with tilemap walls.
    std::shared_ptr<Scene> scene = obj->getScene();
    if (scene->hasTilemap()) {
        Tilemap& tilemap = scene->getTilemap();
        std::vector<Wall> const& walls = tilemap.getWalls();
        for (auto wall : walls) {
            for (auto diag : diagonals) {
                if (diag.intersects(wall.line)) {
                    std::cout << "intersecting\n";
                }
            }
        }
    }
}