#pragma once

#include "components/Component.h"
#include "utils/Math.h"

#include <unordered_map>
#include <typeindex>

class GameObject {
private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
public:
    vec2 position;

    GameObject();

    template<typename T>
    void addComponent(std::shared_ptr<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        components[std::type_index(typeid(T))] = component;
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
};