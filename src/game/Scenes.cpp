#include "scenes.h"

#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"

#include "prefabs.h"

#include <iostream>

void scenes::SampleScene::init() {
    Scene::init();

    int w = 25;
    int s = CHUNK_SIZE * w;
    std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>(s, s, 1.0f);
    std::shared_ptr<SpriteManager> sm = getManagers()->spriteManager;
    int gi = sm->getSpriteIndex("minecraft0");
    int ns = sm->getNumSprites();
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            int si = (i / CHUNK_SIZE * w + j / CHUNK_SIZE) % 800 + gi;
            tilemap->setTile(i, j, {si, false});
        }
    }
    for (float x = -3.0f; x <= 3.0f; x += 1.0f) {
        tilemap->setTileFromWorldPosition(x, -3.0f, {gi + 4, true});
    }
    tilemap->recomputeWallPolygons();
    setTilemap(std::move(tilemap));

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();

    float x = -3.0f;
    for (int i = 128; i < 136; i++) {
        obj = std::make_shared<GameObject>();
        obj->transform.scale = { 1.0f, 1.0f };
        obj->transform.position = { x, 7.0f };
        x += 1.0f;
        obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft" + std::to_string(i)));
        this->addGameObject(obj);
    }

    obj = std::make_shared<GameObject>();
    obj->transform.scale = { 2.0f, 2.0f };
    obj->transform.position = { 0, 9.0f };
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