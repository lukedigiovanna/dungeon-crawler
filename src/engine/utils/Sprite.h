#pragma once

#include "Texture.h"

#include <glm/glm.hpp>

struct Sprite {
    Texture* texture;
    glm::vec4 clip;
};