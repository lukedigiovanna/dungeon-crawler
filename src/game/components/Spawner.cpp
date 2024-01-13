#include "Spawner.h"

#include "../../engine/Scene.h"
#include "../../engine/Engine.h"
#include "../../engine/components/SpriteAnimator.h"
#include "../../engine/components/Physics.h"
#include "../../engine/utils/Graphics.h"
#include "../../engine/utils/Math.h"
#include "../../engine/managers/InputManager.h"

#include "../prefabs.h"

#include <cmath>
#include <iostream>

void Spawner::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    std::shared_ptr<InputManager> input = Engine::getSingleton()->getManagers()->inputManager;
    std::shared_ptr<Scene> scene = obj->getScene();    
    std::shared_ptr<Camera> cam = scene->getCamera();

    if (input->isMouseDown()) {
        this->timer += dt;
        if (this->timer >= this->frequency) {
            for (int i = 0; i < 1; i++) {
                std::shared_ptr<GameObject> newObj = prefabs::spinningCatPrefab();
                std::shared_ptr<Physics> physics = newObj->getComponent<Physics>();
                math::vec2 mouseWorld = cam->screenPositionToWorldPosition(input->getMousePosition());
                newObj->transform.position = { obj->transform.position.x + math::random(-0.05f, 0.05f), obj->transform.position.y + math::random(-0.05f, 0.05f) };
                physics->velocity = (mouseWorld - newObj->transform.position).normalized() * 5.0f;
                scene->addGameObject(newObj);
            }
            
            this->timer = std::fmod(this->timer, this->frequency);
        }
    }
}

void Spawner::init() {
    // std::shared_ptr<SpriteAnimator> animator = getGameObject()->getComponent<SpriteAnimator>();

    // animator->stop();
}