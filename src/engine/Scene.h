#pragma once

#include "GameObject.h"
#include "Window.h"
#include "Tilemap.h"
#include "components/Camera.h"
#include "managers/Managers.h"

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

    std::unique_ptr<Tilemap> tilemap;

    std::shared_ptr<Managers> managers;
public:
    Scene();

    virtual void init();

    void setManagers(std::shared_ptr<Managers> managers);
    std::shared_ptr<Managers> getManagers() const;

    bool hasTilemap() const;
    void setTilemap(std::unique_ptr<Tilemap> tilemap);
    Tilemap& getTilemap() const;

    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void destroyGameObject(std::shared_ptr<GameObject> gameObject);
    std::vector<std::shared_ptr<GameObject>> const& getGameObjects() const; 

    std::shared_ptr<Camera> getCamera() const;

    void render(Window* window) const;
    void update(float dt);
};