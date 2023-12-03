#include "scenes.h"

#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"

#include "prefabs.h"

#include <iostream>

void scenes::SampleScene::init() {
    Scene::init();

    int s = 100;
    std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>(s, s, 0.25f);
    int si = 0;
    std::shared_ptr<SpriteManager> sm = getManagers()->spriteManager;
    int ns = sm->getNumSprites();
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            tilemap->setTile(i, j, si, false);
            si = (si + 1) % ns;
            std::cout << si << "\n";
        }
    }
    setTilemap(std::move(tilemap));

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
    // obj->scale = {20.0f, 11.78f};
    // obj->setRendererComponent(std::make_unique<SpriteRenderer>("background"));
    // this->addGameObject(obj);

    float x = -3.0f;
    for (int i = 128; i < 136; i++) {
        obj = std::make_shared<GameObject>();
        obj->scale = { 1.0f, 1.0f };
        obj->position = { x, 7.0f };
        x += 1.0f;
        obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft" + std::to_string(i)));
        this->addGameObject(obj);
    }

    obj = std::make_shared<GameObject>();
    obj->scale = { 2.0f, 2.0f };
    obj->position = { 0, 9.0f };
    obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft128"));
    obj->addComponent(std::make_shared<SpriteAnimator>("wheat-grow"));
    addGameObject(obj);

    int i = 0;

    // for (float y = -7.0f; y >= -10.0f; y -= 1.0f) {
    //     for (float x = -6.0f; x <= 5.0f; x += 1.0f) {
    //         obj = std::make_shared<GameObject>();
    //         obj->scale = { 1.0f, 1.0f };
    //         obj->position = { x, y };
    //         obj->setRendererComponent(std::make_unique<SpriteRenderer>("character" + std::to_string(i++)));
    //         addGameObject(obj);
    //     }
    // }

    // for (float y = 14.0f; y >= -14.0f; y -= 0.5f) {
    //     for (float x = -14.0f; x <= 14.0f; x += 0.5f) {
    //         obj = std::make_shared<GameObject>();
    //         obj->scale = {0.5f, 0.5f};
    //         obj->position = { x, y };
    //         obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft0"));
    //         obj->addComponent(std::make_shared<SpriteAnimator>("player-walk-right"));
    //         this->addGameObject(obj);
    //     }
    // }

    this->addGameObject(prefabs::playerPrefab());
}