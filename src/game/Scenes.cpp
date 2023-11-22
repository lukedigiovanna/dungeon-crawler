#include "scenes.h"

#include "../engine/GameObject.h"
#include "../engine/components/RendererComponent.h"
#include "../engine/components/SpriteRenderer.h"

#include "components/Spawner.h"
#include "prefabs.h"

void scenes::SampleScene::init() {
    Scene::init();
    this->addGameObject(prefabs::playerPrefab());
}