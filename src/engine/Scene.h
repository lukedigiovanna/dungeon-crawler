#pragma once

#include "GameObject.h"
#include <memory>
#include <vector>

class Scene {
private:
    std::vector<std::weak_ptr<GameObject>> gameObjects;
public:
    Scene();

    void addGameObject(std::weak_ptr<GameObject> gameObject);
};