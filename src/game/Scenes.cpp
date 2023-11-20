#include "Scenes.h"
#include "components/Spawner.h"

void scenes::SampleScene::init() {
    Scene::init();
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
    go->position.x = 2.0f;
    go->position.y = 2.0f;
    std::shared_ptr<RendererComponent> re = std::make_shared<ShapeRenderer>(Shape::SQUARE, gfx::COLOR_BLUE);
    go->setRendererComponent(re);
    std::shared_ptr<Spawner> spawner = std::make_shared<Spawner>();
    go->addComponent(spawner);
    this->addGameObject(go);
}