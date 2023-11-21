#pragma once

#include "../../engine/components/Component.h"

class Spin: public Component {
private:
public:
    void update(float dt) override;
};