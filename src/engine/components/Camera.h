#pragma once

#include "Component.h"

class Camera: public Component {
private:
public:
    float zoomScale;
    Camera();
};