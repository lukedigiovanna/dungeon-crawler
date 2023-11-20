#pragma once

#include "components/Component.h"
#include "components/RendererComponent.h"
#include "utils/Math.h"

#include <unordered_map>
#include <typeindex>

class Scene;

class GameObject: public std::enable_shared_from_this<GameObject> {
private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    std::shared_ptr<RendererComponent> rendererComponent = nullptr;
public:
    std::weak_ptr<Scene> scene;
    vec2 position;
    vec2 scale;

    GameObject();

    template<typename T>
    void addComponent(std::shared_ptr<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        components[std::type_index(typeid(T))] = component;
        components[std::type_index(typeid(T))]->setGameObject(shared_from_this());
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    void setRendererComponent(std::shared_ptr<RendererComponent> rendererComponent);
    void render(Window* window, float x, float y, float width, float height) const;
    bool hasRenderer() const;

    void update(float dt);

    void setScene(std::shared_ptr<Scene> scene);
    
    std::shared_ptr<Scene> getScene() const;
};