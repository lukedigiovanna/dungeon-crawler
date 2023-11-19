#pragma once

#include "Component.h"
#include "../graphics/Window.h"
#include <SDL.h>

class Camera: public Component {
private:
    float scale;
public:
    Camera();

    void update(float dt) override;
    void render(Window* window) const;
};