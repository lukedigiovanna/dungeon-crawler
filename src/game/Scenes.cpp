#include "scenes.h"

#include "../engine/GameObject.h"
#include "../engine/components/RendererComponent.h"
#include "../engine/components/SpriteRenderer.h"

#include "components/Spawner.h"

void scenes::SampleScene::init() {
    Scene::init();
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
    go->scale = {0.5f, 0.5f};
    go->setRendererComponent(std::make_unique<SpriteRenderer>("cat"));
    go->addComponent(std::make_shared<Spawner>());
    this->addGameObject(go);
}