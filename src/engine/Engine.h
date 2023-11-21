#pragma once

#include "Scene.h"
#include "Window.h"
#include "SpriteManager.h"

#include <memory>
#include <thread>
#include <atomic>

class Engine {
private:
    std::shared_ptr<SpriteManager> spriteManager;
    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;

    std::unique_ptr<std::thread> gameThread;

    std::atomic<bool> active;
public:
    static const unsigned int TARGET_TPS = 20;

    Engine(std::string gameName);

    std::shared_ptr<SpriteManager> getSpriteManager() const;

    void loadScene(std::shared_ptr<Scene> scene);

    // Initiates a render thread and a logic thread
    void run();
    void halt();
    void destroy();

    void renderLoop();
    void gameLoop();
};