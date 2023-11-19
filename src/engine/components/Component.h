#pragma once

#include <memory>

class GameObject; // Forward declare the GameObject class

class Component {
protected:
    std::weak_ptr<GameObject> gameObject;
public:
    Component();
    virtual ~Component() = default;

    void setGameObject(std::shared_ptr<GameObject> gameObject);

    // May or may not be overwritten
    void update(float dt);
};