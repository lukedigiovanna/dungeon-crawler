#include "PlayerMovement.h"

#include "../../engine/GameObject.h"
#include "../../engine/Scene.h"
#include "../../engine/Engine.h"
#include "../../engine/managers/InputManager.h"

PlayerMovement::PlayerMovement(float speed) : speed(speed) {

}

void PlayerMovement::init() {
    this->physics = getGameObject()->getComponent<Physics>();
    this->animator = getGameObject()->getComponent<SpriteAnimator>();
}

void PlayerMovement::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    std::shared_ptr<InputManager> input = Engine::getSingleton()->getManagers()->inputManager;
    std::shared_ptr<Scene> scene = obj->getScene();

    std::shared_ptr<Camera> camera = scene->getCamera();
    std::shared_ptr<GameObject> camObj = camera->getGameObject();

    std::shared_ptr<SpriteManager> spriteManager = Engine::getSingleton()->getManagers()->spriteManager;

    // if (scene->hasTilemap()) {
    //     Tilemap& tm = scene->getTilemap();
    //     int si = spriteManager->getSpriteIndex("minecraft0") + 32;
    //     tm.setTileFromWorldPosition(obj->transform.position.x, obj->transform.position.y, si, false);
    // }

    // move cam to the player
    camObj->transform.position += (obj->transform.position - camObj->transform.position) * 2.0f * dt;

    if (input->isKeyDown(SDLK_LSHIFT)) {
        camera->scale /= 1.1f;
    }
    if (input->isKeyDown(SDLK_SPACE)) {
        camera->scale *= 1.1f;
    }

    if (input->isKeyPressed(SDLK_w)) {
        physics->velocity.y = 5;
    }
    physics->velocity.x = 0;
    if (input->isKeyDown(SDLK_a))
        physics->velocity.x -= speed;
    if (input->isKeyDown(SDLK_d))
        physics->velocity.x += speed;

    physics->angularVelocity = 0;
    if (input->isKeyDown(SDLK_e)) {
        physics->angularVelocity += 180;
    }
    if (input->isKeyDown(SDLK_q)) {
        physics->angularVelocity -= 180;
    }

    if (input->isKeyPressed(SDLK_ESCAPE)) {
        Engine::getSingleton()->getManagers()->sceneManager->loadScene("main_menu");
    }
    

    if (physics->velocity.x < 0)
        animator->setAnimation("player-walk-left");
    else if (physics->velocity.x > 0)
        animator->setAnimation("player-walk-right");
    // else if (physics->velocity.y > 0)
    //     animator->setAnimation("player-walk-up");
    // else if (physics->velocity.y < 0)
    //     animator->setAnimation("player-walk-down");

    std::cout << obj->transform.position.x << ", " << obj->transform.position.y << std::endl;
}