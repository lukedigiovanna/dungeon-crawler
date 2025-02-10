#pragma once

#include "Scene.h"
#include "Window.h"
#include "managers/Managers.h"
#include "managers/SpriteManager.h"
#include "managers/InputManager.h"
#include "managers/AnimationManager.h"
#include "utils/Font.h"

#include <memory>
#include <thread>
#include <atomic>

class Engine {
private:
    static std::unique_ptr<Engine> singleton;
    // Managers
    std::shared_ptr<Managers> managers;

    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;

    std::unique_ptr<std::thread> gameThread;

    std::atomic<bool> active;

    void checkForNewScene();
public:
    static const unsigned int TARGET_TPS = 60;
    
    static Engine* getSingleton();

    static void initializeSingleton(std::string const& gameName);

    Engine(std::string const& gameName);

    std::shared_ptr<Managers> getManagers() const;

    // Initiates a render thread and a logic thread
    void run();
    void halt();
    void destroy();

    void renderLoop();
    void gameLoop();
};
