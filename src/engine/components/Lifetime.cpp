#include "Lifetime.h"

#include "../GameObject.h"

Lifetime::Lifetime() : lifetime(-1.0f), age(0.0f) {

}

Lifetime::Lifetime(float lifetime) : lifetime(lifetime), age(0.0f) { 

}

void Lifetime::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();    
    age += dt;
    if (lifetime >= 0.0f && age >= lifetime) {
        obj->destroy();
    }   
}