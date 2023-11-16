#pragma once

#include "components/Component.h"
#include "utils/Math.h"

#include <vector>

class GameObject {
private:
    // std::vector<std::weak_ptr<Component>> components;
public:
    vec2 position;

    GameObject();
};