#include "EnterListener.h"

#include "../../engine/Engine.h"
#include "../../engine/managers/InputManager.h"

#include <memory>

void EnterListener::update(float dt) {
    std::shared_ptr<InputManager> input = Engine::getSingleton()->getManagers()->inputManager;

    if (input->isKeyPressed(SDLK_RETURN)) {
        Engine::getSingleton()->getManagers()->sceneManager->loadScene("sample");
    }
}