#include "Scenes.h"

#include "../engine/Engine.h"
#include "../engine/components/SpriteAnimator.h"
#include "../engine/components/renderers/SpriteRenderer.h"
#include "../engine/utils/Matrix2D.h"
#include "../engine/ui/Canvas.h"
#include "../engine/ui/TextElement.h"
#include "../engine/ui/SpriteElement.h"

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
    SpriteManager& spriteManager = Engine::getSingleton()->getManagers()->spriteManager();
    Matrix2D lsmFG("assets/levels/c1_et_foreground.csv");
    Matrix2D lsmBG("assets/levels/c1_et_background.csv");
    int w = lsmFG.getWidth();
    int h = lsmFG.getHeight();
    int R = 10;
    std::unique_ptr<Tilemap> foreground = std::make_unique<Tilemap>(w * R, h, 1.0f);
    std::unique_ptr<Tilemap> background = std::make_unique<Tilemap>(w * R, h, 1.0f);
    int baseSpriteIndex = spriteManager.getSpriteIndex("minecraft0");
    int value;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w * R; x++) {
            value = lsmFG.getValue(y, x % w);
            if (value >= 0) {
                foreground->setTile(y, x, value + baseSpriteIndex, true);
            }
            value = lsmBG.getValue(y, x % w);
            if (value >= 0) {
                background->setTile(y, x, value + baseSpriteIndex, false);
            }
        }
    }
    foreground->recomputeOccludingWalls();
    addTilemap(std::move(background));
    addTilemap(std::move(foreground));

    setAmbientLightLuminance(0.1f);

    addGameObject(prefabs::playerPrefab());

    FontManager& fontManager = Engine::getSingleton()->getManagers()->fontManager();
    Canvas& canvas = getCanvas();
    const Font* mcFont = fontManager.getFont("minecraft");
    // std::unique_ptr<UIElement> debugInfo = std::make_unique<UIElement>();
    // std::unique_ptr<UIElement> playerPos = std::make_unique<TextElement>(
    //     mcFont, gfx::COLOR_WHITE, TextAlignment::JUSTIFY_LEFT, 18.0f, "<player  pos>"
    // );
    // playerPos->setAnchor(Anchor::TOP_LEFT);
    // playerPos->transform.position = { 10, 10 };
    // playerPos->setTag("_debug_player_pos");
    // canvas.addElement(std::move(playerPos));

    std::unique_ptr<UIElement> container = std::make_unique<SpriteElement>("minecraft0");
    container->transform.scale = { 250.0f, 250.0f };
    container->transform.position = { Window::DEFAULT_WIDTH / 2, Window::DEFAULT_HEIGHT / 2 };
    container->setAnchor(Anchor::ANCHOR_CENTER);
    container->setScaleMode(ScaleMode::SCALE_WITH_WIDTH);
    container->setTag("container");
    container->active = false;

    Anchor presets[9] = {
        ANCHOR_TOP_LEFT, ANCHOR_TOP_CENTER, ANCHOR_TOP_RIGHT,
        ANCHOR_CENTER_LEFT, ANCHOR_CENTER, ANCHOR_CENTER_RIGHT,
        ANCHOR_BOTTOM_LEFT, ANCHOR_BOTTOM_CENTER, ANCHOR_BOTTOM_RIGHT
    };
    TextAlignment alignmentPresets[3] = {
        JUSTIFY_LEFT, JUSTIFY_CENTER, JUSTIFY_RIGHT
    };
    for (int i = 0; i < 9; i++) {
        int xi = i % 3, yi = i / 3;
        float x = xi / 2.0f * container->transform.scale.x;
        float y = yi / 2.0f * container->transform.scale.y;
        std::string id = "minecraft" + std::to_string(i); 
        std::unique_ptr<UIElement> t = std::make_unique<SpriteElement>(id);
        t->setTag(id);
        t->transform.scale = { 30.0f, 30.0f };
        t->transform.position = { x, y };
        t->setAnchor(presets[i]);
        t->setScaleMode(ScaleMode::SCALE_WITH_WIDTH);

        std::unique_ptr<UIElement> txt = std::make_unique<TextElement>(
            mcFont, gfx::COLOR_BLUE, alignmentPresets[i % 3], 8.0f, id + "y"
        );
        txt->transform.scale = { t->transform.scale.x * 2, t->transform.scale.y / 2};
        txt->transform.position = t->transform.scale / 2;
        txt->setTag(id + "_text");
        txt->setAnchor(Anchor::ANCHOR_CENTER);
        txt->setScaleMode(ScaleMode::SCALE_WITH_WIDTH);
        t->addChild(std::move(txt));

        container->addChild(std::move(t));
    }
    canvas.addElement(std::move(container));
}

void scenes::MainMenuScene::setup() {
    std::shared_ptr<GameObject> background = std::make_shared<GameObject>();
    background->setRendererComponent(std::make_unique<SpriteRenderer>("minecraft233"));
    background->transform.scale = { 5.0f, 5.0f };
    background->addComponent(std::make_shared<EnterListener>());

    FontManager& fontManager = Engine::getSingleton()->getManagers()->fontManager();
    Canvas& canvas = getCanvas();
    const Font* mcFont = fontManager.getFont("minecraft");
    
    std::unique_ptr<UIElement> title = std::make_unique<TextElement>(
        mcFont, gfx::COLOR_WHITE, TextAlignment::JUSTIFY_CENTER, 48.0f, "OUBLIETTE"
    );
    title->setAnchor(Anchor::ANCHOR_TOP_CENTER);
    // title->setScaleMode(ScaleMode::SCALE_WITH_WIDTH);
    title->transform.scale = { 300, 48 };
    title->transform.position = { Window::DEFAULT_WIDTH / 2.0f, 70.0f };
    canvas.addElement(std::move(title));

    std::unique_ptr<UIElement> enterToPlay = std::make_unique<TextElement>(
        mcFont, 
        gfx::COLOR_GREEN, 
        TextAlignment::JUSTIFY_CENTER, 
        12.0f, 
        "Press <enter> to play... or don't i don't really care. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
    );
    enterToPlay->setAnchor(Anchor::ANCHOR_TOP_CENTER);
    // enterToPlay->setScaleMode(ScaleMode::SCALE_WITH_WIDTH);
    enterToPlay->transform.position = { Window::DEFAULT_WIDTH / 2.0f, 150.0f };
    canvas.addElement(std::move(enterToPlay));

    addGameObject(background);
}