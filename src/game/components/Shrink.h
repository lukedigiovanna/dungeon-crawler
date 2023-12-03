#pragma once

#include "../../engine/components/Component.h"
#include "../../engine/components/Lifetime.h"
#include "../../engine/components/LightSource.h"

class Shrink: public Component {
private:
    std::shared_ptr<Lifetime> lifetime;
    std::shared_ptr<LightSource> light;
public:
    void init() override;
    void update(float dt) override;
};