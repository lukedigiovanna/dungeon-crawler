#include "prefabs.h"

#include "../engine/components/renderers/SpriteRenderer.h"
#include "../engine/components/renderers/ShapeRenderer.h"
#include "../engine/components/renderers/AnimatedSpriteRenderer.h"
#include "../engine/components/Lifetime.h"
#include "../engine/components/Physics.h"
#include "../engine/components/LightSource.h"
#include "../engine/utils/Math.h"
#include "../engine/utils/meshes.h"
#include "../engine/utils/AnimationController.h"

#include "components/Shrink.h"
#include "components/Spawner.h"

#include <utility>
#include <cmath>
#include <string>

PrefabConstructor prefabs::spinningCatPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> cat = std::make_shared<GameObject>();
    gfx::color color{random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f)};
    cat->setRendererComponent(
        std::make_unique<SpriteRenderer>("minecraft" + std::to_string(rand() % 816), color)
    );
    cat->addComponent(std::make_shared<LightSource>(gfx::COLOR_BLUE, 0.1f));
    cat->addComponent(std::make_shared<Lifetime>(random(1.0f, 2.0f)));
    std::shared_ptr<Physics> physics = std::make_shared<Physics>();
    float angle = random(0.0f, 360.0f);
    float speed = 2.5f;
    physics->velocity = { std::cos(angle) * speed, std::sin(angle) * speed };
    physics->angularVelocity = 90.0f;
    physics->innateDragCoefficient = 0.95f;
    cat->addComponent(physics);
    cat->addComponent(std::make_shared<Shrink>());
    cat->scale = { 0.25f, 0.25f };
    return cat;
};

PrefabConstructor prefabs::playerPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    player->scale = {0.5f, 0.5f};
    player->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft3"));
    player->addComponent(std::make_shared<Spawner>());
    player->addComponent(std::make_shared<LightSource>(gfx::COLOR_WHITE, 1.5f));
    return player;
};