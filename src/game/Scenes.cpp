#include "scenes.h"

#include "../engine/Engine.h"
#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"

#include "prefabs.h"

#include <iostream>

void scenes::SampleScene::setup() {
    int w = 32;
    int s = CHUNK_SIZE * w;
    std::unique_ptr<Tilemap> tilemap = std::make_unique<Tilemap>(s, s, 1.0f);
    std::shared_ptr<SpriteManager> sm = Engine::getSingleton()->getManagers()->spriteManager;
    int gi = sm->getSpriteIndex("minecraft0");
    int ns = sm->getNumSprites();
    math::PerlinNoise pn;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            int cii = i / CHUNK_SIZE * w + j / CHUNK_SIZE;
            if (pn.get(i * 0.25f + 0.5f, j * 0.25f + 0.5f) > 0.2f) {
                tilemap->setTile(i, j, gi + 11, true);
            }
            else {
                tilemap->setTile(i, j, gi + (cii % 10), false);
            }
        }
    }
    // for (float x = -3.0f; x <= 3.0f; x += 1.0f) {
        tilemap->setTileFromWorldPosition(0, -3.0f, gi + 4, true);
    // }
    tilemap->recomputeOccludingWalls();
    setTilemap(std::move(tilemap));
    
    this->addGameObject(prefabs::playerPrefab());
}