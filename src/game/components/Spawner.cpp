#include "Spawner.h"

#include "../../engine/Scene.h"
#include "../../engine/utils/Graphics.h"
#include "../../engine/utils/Math.h"
#include "../../engine/managers/InputManager.h"

#include "../prefabs.h"

#include <cmath>
#include <iostream>

void Spawner::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    std::shared_ptr<InputManager> input = obj->getScene()->getManagers()->inputManager;
    std::shared_ptr<Scene> scene = obj->getScene();    
    
    if (input->isKeyPressed(SDLK_SPACE)) {
        obj->scale = obj->scale * 1.5f;
    }
    if (input->isKeyPressed(SDLK_LSHIFT)) {
        obj->scale = obj->scale / 1.5f;
    }

    if (input->isKeyDown(SDLK_UP)) {
        scene->getCamera()->scale /= 1.1f;
    }
    if (input->isKeyDown(SDLK_DOWN)) {
        scene->getCamera()->scale *= 1.1f;
    }

    
    vec2 mousePos = input->getMousePosition();
    vec2 mouseWorldPos = scene->getCamera()->screenPositionToWorldPosition(mousePos);

    obj->position = mouseWorldPos;

    if (input->isMouseDown()) {
        this->timer += dt;
        if (this->timer >= this->frequency) {
            for (int i = 0; i < 20; i++) {
                std::shared_ptr<GameObject> newObj = prefabs::spinningCatPrefab();
                newObj->position = { obj->position.x + random(-0.05f, 0.05f), obj->position.y + random(-0.05f, 0.05f) };
                scene->addGameObject(newObj);
            }
            
            this->timer = std::fmod(this->timer, this->frequency);
        }
    }
}