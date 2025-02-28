#pragma once

class Scene;

#include <memory>
#include <unordered_map>
#include <string>

class SceneManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> sceneMap;
    std::shared_ptr<Scene> currentScene;
    bool dirty;
public:
    SceneManager();
    SceneManager(const SceneManager&) = delete;
    
    void registerScene(std::shared_ptr<Scene> scene);
    void loadScene(std::string const& sceneId);

    inline std::shared_ptr<Scene> getCurrentScene() const {
        return currentScene;
    }

    inline bool isDirty() const {
        return dirty;
    }

    void makeClean();
};