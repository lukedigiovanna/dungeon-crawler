#include "scenes.h"

#include "../engine/GameObject.h"
#include "../engine/components/RendererComponent.h"
#include "../engine/components/ShapeRenderer.h"

#include "components/Spawner.h"

void scenes::SampleScene::init() {
    Scene::init();
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
    go->position.x = 2.0f;
    go->position.y = 2.0f;
    std::unique_ptr<RendererComponent> re = std::make_unique<ShapeRenderer>(Shape::SQUARE, gfx::COLOR_BLUE);
    // std::unique_ptr<RendererComponent> re = std::unique_ptr<ShapeRenderer>(new ShapeRenderer(Shape::SQUARE, gfx::COLOR_BLUE));
    go->setRendererComponent(std::move(re));
    std::shared_ptr<Spawner> spawner = std::make_shared<Spawner>();
    go->addComponent(spawner);
    this->addGameObject(go);
}