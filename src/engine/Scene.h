#pragma once

#include "GameObject.h"
#include <memory>
#include <vector>
#include <SDL.h>

// All instances of a scene must be managed by a shared_ptr
class Scene: public std::enable_shared_from_this<Scene> {
private:
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
public:
    Scene();

    void addGameObject(std::shared_ptr<GameObject> gameObject);

    void render(SDL_Renderer* renderer) const;
};