#pragma once

#include "Scene.h"
#include "Window.h"
#include "managers/Managers.h"
#include "managers/SpriteManager.h"
#include "managers/InputManager.h"
#include "managers/AnimationManager.h"

#include <memory>
#include <thread>
#include <atomic>

class Engine {
private:
    // Managers
    Managers managers;

    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;

    std::unique_ptr<std::thread> gameThread;

    std::atomic<bool> active;
public:
    static const unsigned int TARGET_TPS = 60;

    Engine(std::string gameName);

    const Managers* getManagers() const;

    void loadScene(std::shared_ptr<Scene> scene);

    // Initiates a render thread and a logic thread
    void run();
    void halt();
    void destroy();

    void renderLoop();
    void gameLoop();
};