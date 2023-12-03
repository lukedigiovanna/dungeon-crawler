#pragma once

#include "components/Component.h"
#include "components/renderers/RendererComponent.h"
#include "utils/Math.h"
#include "utils/Shader.h"

#include <functional>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

class Scene;

class GameObject: public std::enable_shared_from_this<GameObject> {
private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    std::unique_ptr<RendererComponent> rendererComponent = nullptr;
public:
    std::weak_ptr<Scene> scene;
    vec2 position;
    vec2 scale;
    float rotation;

    GameObject();

    // Initializes any components added before the GameObject was added to a scene
    void init();
    void update(float dt);

    void destroy();

    template<typename T>
    void addComponent(std::shared_ptr<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        components[std::type_index(typeid(T))] = component;
        components[std::type_index(typeid(T))]->setGameObject(shared_from_this());
        if (isInScene()) {
            components[std::type_index(typeid(T))]->init();
        }
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        throw std::runtime_error("GameObject::getComponent: Tried getting a component type which is not on the given game object");
        return nullptr;
    }

    template<typename T>
    bool hasComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return true;
        }
        return false;
    }

    void setRendererComponent(std::unique_ptr<RendererComponent> rendererComponent);
    void render(std::shared_ptr<Shader> shader) const;
    bool hasRenderer() const;

    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getScene() const;
    bool isInScene() const;
};

using PrefabConstructor = std::function<std::shared_ptr<GameObject>()>;