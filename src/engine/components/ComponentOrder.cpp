#include "ComponentOrder.h"

#include "Collider.h"
#include "Physics.h"
#include "Lifetime.h"

#include <queue>

ComponentGraph ComponentOrder::dependencyGraph;
std::vector<std::type_index> ComponentOrder::rootBranch;
std::unordered_map<std::type_index, int> ComponentOrder::priorities;
std::unordered_set<std::type_index> ComponentOrder::hasDependent;

bool ComponentOrder::dirty = false;

void ComponentOrder::initialize() {
    addRoot<Lifetime>();
    addDependency<Physics, Collider>();
}

#include <iostream>
void ComponentOrder::updatePriorities() {
    // Compute a topological sort on the dependency graph
    std::unordered_map<std::type_index, int> inDegrees;
    for (auto & [type, dependents] : dependencyGraph) {
        auto f = inDegrees.find(type);
        if (f == inDegrees.end()) {
            inDegrees[type] = 0;
        }
        for (auto & dependent : dependents) {
            inDegrees[dependent]++;
        }
    }

    int p = 0;
    for (auto & type : rootBranch) {
        priorities[type] = p++;
    }

    std::queue<std::type_index> n;
    for (auto & [type, degree] : inDegrees) {
        if (degree == 0)
            n.push(type);
    }
    while (n.size() > 0) {
        auto type = n.front();
        n.pop();
        priorities[type] = p++;
        auto f = dependencyGraph.find(type);
        if (f != dependencyGraph.end()) {
            for (auto & dependent : f->second) {
                inDegrees[dependent]--;
                if (inDegrees[dependent] == 0) {
                    n.push(dependent);
                }
            }
        }
    }

    for (auto & [type, priority] : priorities) {
        std::cout << type.name() << ": " << priority << "\n";
    }

    dirty = false;
}

int ComponentOrder::getPriority(std::type_index const& type) {
    auto f = priorities.find(type);
    if (f == priorities.end()) {
        return priorities.size(); // Default is to place component at end of root branch (no dependencies)
    }

    return f->second;
}