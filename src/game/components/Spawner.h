#pragma once

#include "../../engine/components/Component.h"

class Spawner: public Component {
private:
    float timer = 0.0f;
    float frequency = 0.5f;
public:
    void update(float dt) override;
    void init() override;
};