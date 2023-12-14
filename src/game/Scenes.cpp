#include "scenes.h"

#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"

#include "prefabs.h"

#include <iostream>

void scenes::SampleScene::init() {
    Scene::init();

    int w = 4;
    int s = CHUNK_SIZE * w;
    std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>(s, s, 1.0f);
    std::shared_ptr<SpriteManager> sm = getManagers()->spriteManager;
    int gi = sm->getSpriteIndex("minecraft0");
    int ns = sm->getNumSprites();
    math::PerlinNoise pn;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            // if (pn.get(i * 0.25f + 0.5f, j * 0.25f + 0.5f) > 0.2f) {
            //     tilemap->setTile(i, j, {gi + 4, true});
            // }
            // else {
                tilemap->setTile(i, j, gi, false);
            // }
        }
    }
    // for (float x = -3.0f; x <= 3.0f; x += 1.0f) {
        tilemap->setTileFromWorldPosition(0, -3.0f, gi + 4, true);
    // }
    tilemap->recomputeWallPolygons();
    setTilemap(std::move(tilemap));

    // std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();

    // float x = -3.0f;
    // for (int i = 128; i < 136; i++) {
    //     obj = std::make_shared<GameObject>();
    //     obj->transform.scale = { 1.0f, 1.0f };
    //     obj->transform.position = { x, 7.0f };
    //     x += 1.0f;
    //     obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft" + std::to_string(i)));
    //     this->addGameObject(obj);
    // }

    // obj = std::make_shared<GameObject>();
    // obj->transform.scale = { 2.0f, 2.0f };
    // obj->transform.position = { 0, 9.0f };
    // obj->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft128"));
    // obj->addComponent(std::make_shared<SpriteAnimator>("wheat-grow"));
    // addGameObject(obj);

    this->addGameObject(prefabs::playerPrefab());
}