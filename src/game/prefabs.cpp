#include "prefabs.h"

#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/Lifetime.h"

#include "components/Spin.h"

#include <utility>

PrefabConstructor prefabs::spinningCatPrefab = []() -> std::shared_ptr<GameObject> {
    std::shared_ptr<GameObject> cat = std::make_shared<GameObject>();
    cat->setRendererComponent(std::make_unique<SpriteRenderer>("smile"));
    cat->addComponent(std::make_shared<Spin>());
    cat->addComponent(std::make_shared<Lifetime>(7.5f));
    return cat;
};