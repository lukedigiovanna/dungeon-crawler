#pragma once

#include "components/Component.h"
#include "components/ComponentOrder.h"
#include "components/renderers/RendererComponent.h"
#include "utils/Math.h"
#include "utils/Shader.h"

#include <functional>
#include <map>
#include <typeindex>
#include <stdexcept>

class Scene;

struct PriorityComparison {
    bool operator()(std::type_index const& lhs, std::type_index const& rhs) const {
        int c1 = ComponentOrder::getPriority(lhs), c2 = ComponentOrder::getPriority(rhs);
        if (c1 == c2) {
            return lhs < rhs;
        }
        return c1 < c2;
    }
};

#include <iostream>

class GameObject: public std::enable_shared_from_this<GameObject> {
private:
    std::map<std::type_index, std::shared_ptr<Component>, PriorityComparison> components;
    std::unique_ptr<RendererComponent> rendererComponent = nullptr;
public:
    std::weak_ptr<Scene> scene;
    math::Transform transform;

    GameObject();

    // Initializes any components added before the GameObject was added to a scene
    void init();
    void update(float dt);

    void destroy();

    template<typename T>
    void addComponent(std::shared_ptr<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto type_ind = std::type_index(typeid(T));
        components[type_ind] = component;
        components[type_ind]->setGameObject(shared_from_this());
        if (isInScene()) {
            components[type_ind]->init();
        }
    }

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(it->second);
            if (ptr == nullptr) {
                throw std::runtime_error("GameObject::getComponent: Tried getting a component type which is not on the given game object");
            }
            return ptr;
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
    RendererComponent& getRendererComponent() const;

    void render(Shader& shader) const;
    bool hasRenderer() const;

    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getScene() const;
    bool isInScene() const;
};

using PrefabConstructor = std::function<std::shared_ptr<GameObject>()>;