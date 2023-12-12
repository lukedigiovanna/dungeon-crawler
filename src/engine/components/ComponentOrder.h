#pragma once

#include "Component.h"

#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Key: The type that is a dependency
// Values: The values that depend on the key to be executed first.
using ComponentGraph = std::unordered_map<std::type_index, std::vector<std::type_index>>;

class ComponentOrder {
private:    
    static ComponentGraph dependencyGraph;
    static std::vector<std::type_index> rootBranch;

    static std::unordered_map<std::type_index, int> priorities;

    static std::unordered_set<std::type_index> hasDependent;

    static bool dirty;
public:
    // Makes T a dependency of S
    template<typename S, typename T>
    static void addDependency() {
        static_assert(std::is_base_of<Component, S>::value, "S must be a Component type");
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto s = std::type_index(typeid(S));
        auto t = std::type_index(typeid(T));
        if (std::find(rootBranch.begin(), rootBranch.end(), s) != rootBranch.end()) {
            throw std::runtime_error("ComponentOrder::addDependency: Cannot make a dependency which is part of the root branch");
        }
        if (std::find(rootBranch.begin(), rootBranch.end(), t) != rootBranch.end()) {
            throw std::runtime_error("ComponentOrder::addDependency: Cannot make a dependent which is part of the root branch");
        }
        hasDependent.insert(t);
        dependencyGraph[s].push_back(t);
        dirty = true;
    }

    template<typename T>
    static void addRoot() {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        auto t = std::type_index(typeid(T));
        if (hasDependent.find(t) != hasDependent.end()) {
            throw std::runtime_error("ComponentOrder::addRoot: Cannot add a component to the root branch which is already a dependent");
        }
        if (dependencyGraph.find(t) != dependencyGraph.end()) {
            throw std::runtime_error("ComponentOrder::addRoot: Cannot add a component to the root branch which is already a dependency");
        }
        rootBranch.push_back(t);
        dirty = true;
    }

    static void initializeEngineDependencies();
    static void updatePriorities();

    template <typename T>
    static int getPriority() {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component type");
        if (dirty) {
            throw std::runtime_error("Cannot get priority of any type as the dependencies have changed since the last call to ComponentOrder::updatePriorities or it was never called.");
        }

        return getPriority(std::type_index(typeid(T)));
    }

    static int getPriority(std::type_index const& type);
};