#include "prefabs.h"

#include "../engine/components/renderers/SpriteRenderer.h"
#include "../engine/components/renderers/ShapeRenderer.h"
#include "../engine/components/Lifetime.h"
#include "../engine/components/Physics.h"
#include "../engine/components/LightSource.h"
#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/Collider.h"
#include "../engine/utils/Math.h"
#include "../engine/utils/meshes.h"

#include "components/Shrink.h"
#include "components/Spawner.h"
#include "components/PlayerMovement.h"

#include <utility>
#include <cmath>
#include <string>

PrefabConstructor prefabs::spinningCatPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> cat = std::make_shared<GameObject>("Spinning");
    cat->setRendererComponent(
        std::make_unique<SpriteRenderer>("minecraft" + std::to_string(rand() % 816), gfx::COLOR_WHITE)
    );
    cat->addComponent(std::make_shared<LightSource>(gfx::color{0.9f, 0.9f, 1.0f}, 0.25f, true));
    cat->addComponent(std::make_shared<Lifetime>(math::random(5.0f, 8.0f)));
    cat->addComponent(std::make_shared<Collider>());
    std::shared_ptr<Physics> physics = std::make_shared<Physics>();
    float angle = math::random(0.0f, 360.0f);
    float speed = 2.5f;
    physics->angularVelocity = 90.0f;
    physics->dragCoefficient = 0.95f;
    physics->gravity = 10.0f;
    physics->bounciness = 1.0f;
    cat->addComponent(physics);
    cat->addComponent(std::make_shared<Shrink>());
    cat->transform.scale = { 0.25f, 0.25f };
    return cat;
};

PrefabConstructor prefabs::playerPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>("Player");
    player->setRendererComponent(std::make_unique<SpriteRenderer>("idle0"));
    player->addComponent(std::make_shared<SpriteAnimator>("player-idle"));
    player->addComponent(std::make_shared<Spawner>());
    player->addComponent(std::make_shared<LightSource>(gfx::COLOR_WHITE, 0.5f, true));
    player->addComponent(std::make_shared<PlayerMovement>(5.0f));
    player->addComponent(std::make_shared<Collider>());
    player->addComponent(std::make_shared<Lifetime>());
    std::shared_ptr<Physics> physics = std::make_shared<Physics>();
    physics->gravity = 10;
    physics->bounciness = 0.5f;
    player->addComponent(physics);
    player->transform.position = { 2.0f, 18.0f };
    player->transform.scale = {2.0f, 2.0f};
    return player;
};