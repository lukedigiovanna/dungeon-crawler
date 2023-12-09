#pragma once

#include <memory>

class GameObject; // Forward declare the GameObject class

class Component {
private:
    std::weak_ptr<GameObject> gameObject;
protected:
    const int priority; // Determines execution order
public:
    Component();
    virtual ~Component() = default;

    std::shared_ptr<GameObject> getGameObject() const;
    void setGameObject(std::shared_ptr<GameObject> gameObject);

    // May or may not be overwritten
    virtual void update(float dt);
    virtual void init();
};