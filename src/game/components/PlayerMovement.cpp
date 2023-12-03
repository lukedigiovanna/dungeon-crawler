#include "PlayerMovement.h"

#include "../../engine/GameObject.h"
#include "../../engine/Scene.h"
#include "../../engine/managers/InputManager.h"

PlayerMovement::PlayerMovement(float speed) : speed(speed) {

}

void PlayerMovement::init() {
    this->physics = getGameObject()->getComponent<Physics>();
    this->animator = getGameObject()->getComponent<SpriteAnimator>();
}

void PlayerMovement::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    std::shared_ptr<InputManager> input = obj->getScene()->getManagers()->inputManager;
    std::shared_ptr<Scene> scene = obj->getScene();

    std::shared_ptr<Component> camera = scene->getCamera();
    std::shared_ptr<GameObject> camObj = camera->getGameObject();

    // move cam to the player
    camObj->position = obj->position;

    physics->velocity = {0, 0};
    if (input->isKeyDown(SDLK_w))
        physics->velocity.y += speed;
    if (input->isKeyDown(SDLK_s))
        physics->velocity.y -= speed;
    if (input->isKeyDown(SDLK_a))
        physics->velocity.x -= speed;
    if (input->isKeyDown(SDLK_d))
        physics->velocity.x += speed;

    if (physics->velocity.x < 0)
        animator->setAnimation("player-walk-left");
    else if (physics->velocity.x > 0)
        animator->setAnimation("player-walk-right");
    else if (physics->velocity.y > 0)
        animator->setAnimation("player-walk-up");
    else if (physics->velocity.y < 0)
        animator->setAnimation("player-walk-down");

}