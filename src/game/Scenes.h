#pragma once

#include "../engine/Scene.h"

#define declareScene(name) \
class name: public Scene { \
    using Scene::Scene; \
    protected: \
        void setup() override; \
}

namespace scenes {
declareScene(SampleScene);
declareScene(MainMenuScene);
}