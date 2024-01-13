#pragma once

#include "../../engine/components/Component.h"

class EnterListener: public Component {
public:
    void update(float dt) override;
};