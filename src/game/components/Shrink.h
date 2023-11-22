#pragma once

#include "../../engine/components/Component.h"
#include "../../engine/components/Lifetime.h"

class Shrink: public Component {
private:
    std::shared_ptr<Lifetime> lifetime;
public:
    void init() override;
    void update(float dt) override;
};