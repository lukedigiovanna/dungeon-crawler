#pragma once

#include <memory>

class GameObject; // Forward declare the GameObject class

class Component {
private:
    std::shared_ptr<GameObject> gameObject;
public:
    Component();
    virtual ~Component() = default;

    // May or may not be overwritten
    void update(float dt);
};