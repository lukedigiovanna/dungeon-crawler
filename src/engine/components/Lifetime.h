#pragma once

#include "Component.h"

// 
class Lifetime: public Component {
private:
    float age;
    float lifetime;
public:
    Lifetime();
    Lifetime(float lifetime);

    void update(float dt) override;

    inline float getAge() const {
        return this->age;
    }
};