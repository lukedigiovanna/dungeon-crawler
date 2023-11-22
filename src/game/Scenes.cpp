#include "scenes.h"

#include "prefabs.h"

void scenes::SampleScene::init() {
    Scene::init();
    this->addGameObject(prefabs::playerPrefab());
}