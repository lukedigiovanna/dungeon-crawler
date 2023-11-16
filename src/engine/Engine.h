#pragma once

#include "Scene.h"
#include "graphics/Window.h"

#include <memory>
#include <thread>
#include <atomic>

class Engine {
private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Scene> scene;    

    std::unique_ptr<std::thread> renderThread;
    std::unique_ptr<std::thread> gameThread;

    std::atomic<bool> active;
public:
    Engine(std::string gameName);

    // Initiates a render thread and a logic thread
    void start();
    void join();
    void halt();

    void renderLoop();
    void gameLoop();
};