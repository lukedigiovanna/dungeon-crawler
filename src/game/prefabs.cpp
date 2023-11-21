#include "prefabs.h"

#include "../engine/components/SpriteRenderer.h"

#include "components/Spin.h"

#include <utility>

PrefabConstructor prefabs::spinningCatPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> cat = std::make_shared<GameObject>();
    cat->setRendererComponent(std::make_unique<SpriteRenderer>());
    std::shared_ptr<Spin> spin = std::make_shared<Spin>();
    cat->addComponent(spin);
    return cat;
};