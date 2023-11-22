#include "prefabs.h"

#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/ShapeRenderer.h"
#include "../engine/components/Lifetime.h"
#include "../engine/components/Physics.h"
#include "../engine/utils/Math.h"

#include <utility>
#include <cmath>

PrefabConstructor prefabs::spinningCatPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> cat = std::make_shared<GameObject>();
    cat->setRendererComponent(std::make_unique<SpriteRenderer>("character0"));
    // cat->setRendererComponent(std::make_unique<ShapeRenderer>(
    //     Shape::SQUARE, 
    //     gfx::color{random(0, 256), random(0, 256), random(0, 256), random(0, 256)}
    // ));
    cat->addComponent(std::make_shared<Lifetime>(random(3.0f, 4.0f)));
    std::shared_ptr<Physics> physics = std::make_shared<Physics>();
    float angle = random(0.0f, 360.0f);
    float speed = 2.5f;
    physics->velocity = { std::cosf(angle) * speed, std::sinf(angle) * speed };
    physics->angularVelocity = random(-720.0f, 720.0f);
    physics->innateDragCoefficient = 0.9f;
    cat->addComponent(physics);
    cat->scale = { 0.1f, 0.1f };
    return cat;
};