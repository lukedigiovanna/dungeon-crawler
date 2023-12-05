#pragma once

#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>

struct Sprite {
    Texture* texture;
    glm::vec4 clip;

    void render(Shader const& shader) const;
};