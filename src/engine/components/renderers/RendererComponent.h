#pragma once

#include "../../Window.h"
#include "../../utils/Shader.h"

#include <memory>
#include <string>

class GameObject;

class RendererComponent {
private:
    std::weak_ptr<GameObject> gameObject;

    Shader& getShader(std::string const& shaderId) const;
public:
    RendererComponent();
    ~RendererComponent();

    virtual void init();
    virtual void update(float dt);

    std::shared_ptr<GameObject> getGameObject() const;
    void setGameObject(std::shared_ptr<GameObject> obj);

    virtual void render(Shader& shader) const;
};