#pragma once

#include "GameObject.h"
#include "Window.h"
#include "Tilemap.h"
#include "utils/Light.h"
#include "components/Camera.h"
#include "managers/Managers.h"
#include "ui/Canvas.h"

#include <memory>
#include <vector>
#include <SDL.h>

// All instances of a scene must be managed by a shared_ptr
class Scene: public std::enable_shared_from_this<Scene> {
private:
    bool initialized = false;

    std::string id;

    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    std::vector<std::shared_ptr<GameObject>> addGameObjectQueue;
    std::vector<std::shared_ptr<GameObject>> destroyGameObjectQueue;

    // Order of maps dictates render order (first gets rendered first)
    std::vector<std::unique_ptr<Tilemap>> tilemaps;
    
    Canvas canvas;

    Light ambientLight;
protected:
    virtual void setup();

public:
    Scene(const std::string& id);
    
    void init();

    bool hasTilemap() const;
    void addTilemap(std::unique_ptr<Tilemap> tilemap);
    std::vector<std::unique_ptr<Tilemap>>& getTilemaps();

    inline Canvas& getCanvas() {
        return canvas;
    }

    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void destroyGameObject(std::shared_ptr<GameObject> gameObject);
    std::vector<std::shared_ptr<GameObject>> const& getGameObjects() const; 

    std::shared_ptr<Camera> getCamera() const;

    void setAmbientLight(float luminance, gfx::color const& color);
    void setAmbientLightLuminance(float luminance);
    void setAmbientLightColor(gfx::color const& color);

    inline Light const& getAmbientLight() const {
        return ambientLight;
    }

    inline bool isInitialized() const {
        return initialized;
    }

    void render(Window* window) const;
    void update(float dt);

    inline const std::string& getID() const {
        return id;
    }
};