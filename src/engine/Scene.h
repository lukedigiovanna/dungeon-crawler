#pragma once

#include "GameObject.h"
#include "components/Camera.h"
#include "Window.h"
#include "SpriteManager.h"

#include <memory>
#include <vector>
#include <SDL.h>

// All instances of a scene must be managed by a shared_ptr
class Scene: public std::enable_shared_from_this<Scene> {
private:
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    std::vector<std::shared_ptr<GameObject>> addGameObjectQueue;
    std::vector<std::shared_ptr<GameObject>> destroyGameObjectQueue;

    std::shared_ptr<SpriteManager> spriteManager;
public:
    Scene();

    virtual void init();

    void setSpriteManager(std::shared_ptr<SpriteManager> spriteManager);
    std::shared_ptr<SpriteManager> getSpriteManager() const;

    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void destroyGameObject(std::shared_ptr<GameObject> gameObject);
    std::vector<std::shared_ptr<GameObject>> const& getGameObjects() const; 

    void render(Window* window) const;
    void update(float dt);
};