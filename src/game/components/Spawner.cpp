#include "Spawner.h"

#include "../../engine/Scene.h"
#include "../../engine/components/ShapeRenderer.h"
#include "../../engine/components/SpriteRenderer.h"
#include "../../engine/utils/Graphics.h"
#include "../../engine/utils/Math.h"

#include "../prefabs.h"

#include <cmath>


void Spawner::update(float dt) {
    this->timer += dt;
    if (this->timer >= this->frequency) {
        std::shared_ptr<GameObject> obj = this->getGameObject();
        std::shared_ptr<Scene> scene = obj->getScene();

        std::shared_ptr<GameObject> newObj = prefabs::spinningCatPrefab();
        newObj->scale = { 0.5f, 0.5f };
        newObj->position = { random(-3.0f, 3.0f), random(-3.0f, 3.0f) };
        scene->addGameObject(newObj);
        
        this->timer = std::fmod(this->timer, this->frequency);
    }
}