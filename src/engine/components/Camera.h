#pragma once

#include "Component.h"
#include "../Window.h"
#include "../utils/Math.h"
#include <SDL.h>

class Camera: public Component {
private:
    float scale;
    float rotation;
    vec2 windowDimension;
    float aspectRatio;
public:
    Camera();

    void update(float dt) override;
    void init() override;
    
    void render(Window* window);

    vec2 screenPositionToWorldPosition(vec2 screenPosition) const; 
};