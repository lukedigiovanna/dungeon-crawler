#include "scenes.h"

#include "../engine/Engine.h"
#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"
#include "../engine/utils/Matrix2D.h"

#include "components/EnterListener.h"

#include "prefabs.h"

#include <iostream>

void scenes::SampleScene::setup() {
    // int w = 32;
    // int s = CHUNK_SIZE * w;
    // std::shared_ptr<SpriteManager> sm = Engine::getSingleton()->getManagers()->spriteManager;
    // std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>(s, s, 1.0f);
    // int gi = sm->getSpriteIndex("minecraft0");
    // std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>("assets/levels/diamond_passageway_foreground.csv", gi, 1.0f);
    // int w = tilemap->getWidth();
    // int h = tilemap->getHeight();
    // int ns = sm->getNumSprites();
    // math::PerlinNoise pn;
    // for (int i = 0; i < h; i++) {
    //     for (int j = 0; j < w; j++) {
    //         // int cii = i / CHUNK_SIZE * w + j / CHUNK_SIZE;
    //         if (pn.get(i * 0.25f + 0.5f, j * 0.25f + 0.5f) > 0.2f) {
    //             tilemap->setTile(i, j, sm->getSpriteIndex("minecraft4"), true);
    //         }
    //         // else {
    //         //     tilemap->setTile(i, j, gi + (cii % 10), false);
    //         // }
    //     }
    // }
    std::shared_ptr<SpriteManager> spriteManager = Engine::getSingleton()->getManagers()->spriteManager;
    Matrix2D lsmFG("assets/levels/diamond_passageway_foreground.csv");
    Matrix2D lsmBG("assets/levels/diamond_passageway_background.csv");
    int w = lsmFG.getWidth();
    int h = lsmFG.getHeight();
    std::unique_ptr<Tilemap> foreground = std::make_unique<Tilemap>(w, h, 1.0f);
    std::unique_ptr<Tilemap> background = std::make_unique<Tilemap>(w, h, 1.0f);
    int baseSpriteIndex = spriteManager->getSpriteIndex("minecraft0");
    int value;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            value = lsmFG.getValue(y, x);
            if (value >= 0) {
                foreground->setTile(y, x, value + baseSpriteIndex, true);
            }
            value = lsmBG.getValue(y, x);
            if (value >= 0) {
                background->setTile(y, x, value + baseSpriteIndex, false);
            }
        }
    }
    foreground->recomputeOccludingWalls();
    addTilemap(std::move(background));
    addTilemap(std::move(foreground));

    setAmbientLightLuminance(0.5f);

    addGameObject(prefabs::playerPrefab());
}

void scenes::MainMenuScene::setup() {
    std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
    background->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft0"));
    background->transform.scale = { 5.0f, 5.0f };
    background->addComponent(std::make_shared<EnterListener>());
    addGameObject(background);
}