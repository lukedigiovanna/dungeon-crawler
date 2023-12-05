#pragma once

#include "Component.h"
#include "../Window.h"
#include "../utils/Math.h"
#include <SDL.h>

class Camera: public Component {
private:
    math::vec2 windowDimension;
    float aspectRatio;
public:
    float scale;
    float rotation;
    Camera();

    void update(float dt) override;
    void init() override;
    
    void render(Window* window);

    math::vec2 screenPositionToWorldPosition(math::vec2 screenPosition) const; 
};