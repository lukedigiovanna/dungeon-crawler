#pragma once

#include "../../Window.h"

class GameObject;

class RendererComponent {
private:
    std::weak_ptr<GameObject> gameObject;
public:
    RendererComponent();
    ~RendererComponent();

    virtual void init();
    virtual void update(float dt);

    std::shared_ptr<GameObject> getGameObject() const;
    void setGameObject(std::shared_ptr<GameObject> obj);

    virtual void render(Window* window, float x, float y, float width, float height) const;
};