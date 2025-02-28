#include "PlayerMovement.h"

#include "../../engine/GameObject.h"
#include "../../engine/Scene.h"
#include "../../engine/Engine.h"
#include "../../engine/managers/InputManager.h"
#include "../../engine/ui/TextElement.h"

PlayerMovement::PlayerMovement(float speed) : speed(speed) {

}

void PlayerMovement::init() {
    std::shared_ptr<GameObject> obj = getGameObject();
    this->physics = obj->getComponent<Physics>();
    this->animator = obj->getComponent<SpriteAnimator>();
    obj->getScene()->getCamera()->getGameObject()->transform.position = obj->transform.position;
}

void PlayerMovement::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    InputManager& input = Engine::getSingleton()->getManagers()->inputManager();
    std::shared_ptr<Scene> scene = obj->getScene();

    std::shared_ptr<Camera> camera = scene->getCamera();
    std::shared_ptr<GameObject> camObj = camera->getGameObject();

    // move cam to the player
    camObj->transform.position += (obj->transform.position - camObj->transform.position) * 4.0f * dt;

    if (input.isKeyDown(SDLK_LSHIFT)) {
        camera->scale /= 1.1f;
    }
    if (input.isKeyDown(SDLK_SPACE)) {
        camera->scale *= 1.1f;
    }

    if (input.isKeyPressed(SDLK_w)) {
        physics->velocity.y = 6.5f;
    }
    
    float targetSpeed = 0;
    if (input.isKeyDown(SDLK_a))
        targetSpeed -= speed;
    if (input.isKeyDown(SDLK_d))
        targetSpeed += speed;
    if (targetSpeed != 0) 
        physics->velocity.x = targetSpeed;
    else {
        physics->velocity.x *= std::exp(-10 * dt);
    }

    physics->angularVelocity = 0;
    if (input.isKeyDown(SDLK_e)) {
        physics->angularVelocity += 180;
    }
    if (input.isKeyDown(SDLK_q)) {
        physics->angularVelocity -= 180;
    }

    if (input.isKeyPressed(SDLK_ESCAPE)) {
        Engine::getSingleton()->getManagers()->sceneManager().loadScene("main_menu");
    }

    if (std::abs(physics->velocity.x) > 1e-4) {
        animator->setAnimation("player-run");
    }
    else {
        animator->setAnimation("player-idle");
    }

    if (physics->velocity.x < 0) {
        obj->transform.scale.x = -std::abs(obj->transform.scale.x);
    }
    else if (physics->velocity.x > 0) {
        obj->transform.scale.x = std::abs(obj->transform.scale.x);
    }

    Canvas& canvas = obj->getScene()->getCanvas();
    UIElement* playerPos = canvas.getElementByTag("_debug_player_pos");
    if (playerPos) {
        TextElement* textPlayerPos = dynamic_cast<TextElement*>(playerPos);
        if (textPlayerPos) {
            std::string pos =
                "x, y = " +
                std::to_string(static_cast<int>(obj->transform.position.x)) +
                ", " + 
                std::to_string(static_cast<int>(obj->transform.position.y));
            textPlayerPos->setText(pos);
        }
    }
}