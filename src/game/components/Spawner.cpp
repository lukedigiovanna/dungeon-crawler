#include "Spawner.h"

#include "../../engine/Scene.h"
#include "../../engine/components/ShapeRenderer.h"
#include "../../engine/components/SpriteRenderer.h"
#include "../../engine/utils/Graphics.h"
#include "../../engine/utils/Math.h"

#include "../prefabs.h"

#include <cmath>
#include <iostream>

void Spawner::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    std::shared_ptr<InputManager> input = obj->getScene()->getInputManager();
    
    if (input->isKeyDown(SDLK_d)) {
        obj->position.x += dt;
    }
    if (input->isKeyDown(SDLK_a)) {
        obj->position.x -= dt;
    }
    if (input->isKeyDown(SDLK_w)) {
        obj->position.y += dt;
    }
    if (input->isKeyDown(SDLK_s)) {
        obj->position.y -= dt;
    }
    
    if (input->isKeyPressed(SDLK_SPACE)) {
        obj->scale = obj->scale * 1.5f;
    }
    if (input->isKeyPressed(SDLK_LSHIFT)) {
        obj->scale = obj->scale / 1.5f;
    }

    std::shared_ptr<Scene> scene = obj->getScene();    
    
    vec2 mousePos = input->getMousePosition();
    vec2 mouseWorldPos = scene->getCamera()->screenPositionToWorldPosition(mousePos);

    obj->position = mouseWorldPos;

    this->timer += dt;
    if (this->timer >= this->frequency) {

        std::shared_ptr<GameObject> newObj = prefabs::spinningCatPrefab();
        newObj->scale = { 0.25f, 0.25f };
        newObj->position = { obj->position.x + random(-0.5f, 0.5f), obj->position.y + random(-0.5f, 0.5f) };
        scene->addGameObject(newObj);
        
        this->timer = std::fmod(this->timer, this->frequency);
    }
}