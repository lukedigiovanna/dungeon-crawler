#include "Collider.h"

#include "../GameObject.h"
#include "../Scene.h"
#include "Physics.h"

Collider::Collider() {
    polygon.points.resize(4);
}

#include <iostream>
void Collider::regeneratePolygon() {
    std::shared_ptr<GameObject> obj = getGameObject();
    transform = obj->transform;

    polygon.points[0] = math::vec2{+transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    polygon.points[1] = math::vec2{+transform.scale.x / 2.0f, -transform.scale.y / 2.0f};    
    polygon.points[2] = math::vec2{-transform.scale.x / 2.0f, -transform.scale.y / 2.0f};
    polygon.points[3] = math::vec2{-transform.scale.x / 2.0f, +transform.scale.y / 2.0f};
    
    float rad = math::degToRad(transform.rotation);
    float cos = std::cos(rad), sin = std::sin(rad);
    for (size_t i = 0; i < 4; i++) {
        auto [x, y] = polygon.points[i];
        polygon.points[i] = transform.position + math::vec2{
            x * cos - y * sin,
            x * sin + y * cos
        };
    }

    polygon.center = transform.position;

    // std::cout << transform.position.x << ", " << transform.position.y << 
    //     "\n\t x " << polygon.points[0].x << ", " << polygon.points[0].y << 
    //     "\n\t x " << polygon.points[1].x << ", " << polygon.points[1].y << 
    //     "\n\t x " << polygon.points[2].x << ", " << polygon.points[2].y <<
    //     "\n\t x " << polygon.points[3].x << ", " << polygon.points[3].y << std::endl;
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
        math::Rectangle rect = math::getBoundingRectangle(polygon);
        // std::cout << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << "\n";
        for (float y = rect.y; y < rect.y + rect.height + scale; y += scale) {
            for (float x = rect.x; x < rect.x + rect.width + scale; x += scale) {
                Tile const& tile = tilemap.getTileFromWorldPosition(x, y);
                if (tile.wall) {
                    math::Polygon const& wall = tile.getWallPolygon();
                    math::SATResult result = checkCollision_SAT(polygon, wall);
                    if (result.collided) {
                        math::vec2 cd = (transform.position - wall.center).normalized();
                        math::vec2 d = result.overlapAxis;
                        if (math::dot(cd, d) < 0) d *= -1;
                        math::vec2 correction = d * result.overlap;
                        obj->transform.position += correction;
                        if (obj->hasComponent<Physics>()) {
                            std::shared_ptr<Physics> physics = obj->getComponent<Physics>();
                            physics->velocity = physics->velocity - d * (physics->bounciness * 2 * math::dot(physics->velocity, d));
                        }
                        regeneratePolygon();
                    }
                }
            }
        }
        // From the polygon, generate a bounding box of the polygon

        // std::vector<math::Polygon> const& walls = tilemap.getWallPolygons();
        // for (auto wall : walls) {
        //     math::SATResult result = checkCollision_SAT(polygon, wall);
        //     if (result.collided) {
        //         // std::cout << transform.position.x << "\n";
        //         math::vec2 cd = (transform.position - wall.center).normalized();
        //         math::vec2 d = result.overlapAxis;
        //         if (math::dot(cd, d) < 0) d *= -1;
        //         math::vec2 correction = d * result.overlap;
        //         obj->transform.position += correction;
        //         if (obj->hasComponent<Physics>()) {
        //             std::shared_ptr<Physics> physics = obj->getComponent<Physics>();
        //             physics->velocity = physics->velocity - d * (2 * math::dot(physics->velocity, d));
        //         }
        //         regeneratePolygon();
        //     }
        // }
    }
}