#include "scenes.h"

#include "../engine/components/renderers/SpriteRenderer.h"

#include "prefabs.h"

void scenes::SampleScene::init() {
    Scene::init();
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
    obj->scale = {20.0f, 11.78f};
    obj->setRendererComponent(std::make_unique<SpriteRenderer>("background"));
    this->addGameObject(obj);
    this->addGameObject(prefabs::playerPrefab());
}