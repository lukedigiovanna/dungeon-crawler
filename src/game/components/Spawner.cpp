#include "Spawner.h"

#include "../../engine/Scene.h"
#include "../../engine/components/ShapeRenderer.h"
#include "../../engine/utils/Graphics.h"
#include "../../engine/utils/Math.h"

void Spawner::update(float dt) {
    this->timer += dt;
    if (this->timer >= this->frequency) {
        std::shared_ptr<GameObject> obj = this->getGameObject();
        std::shared_ptr<Scene> scene = obj->getScene();
        std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>();
        newObj->scale = { 0.5f, 0.5f };
        newObj->position = { random(-3.0f, 3.0f), random(-3.0f, 3.0f) };
        std::shared_ptr<ShapeRenderer> renderer = std::make_shared<ShapeRenderer>(Shape::SQUARE, gfx::COLOR_GREEN);
        newObj->setRendererComponent(renderer);
        scene->addGameObject(newObj);
    }
}