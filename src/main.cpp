#include <SDL.h>
#include <iostream>
#include <memory>

#include "engine/Engine.h"
#include "engine/Scene.h"
#include "game/Scenes.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Engine engine("Cool");
    std::shared_ptr<Scene> startingScene = std::make_shared<scenes::SampleScene>();
    engine.loadScene(startingScene);
    engine.run();

    SDL_Quit();

    return 0;
}
