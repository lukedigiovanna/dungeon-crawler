#include "SceneManager.h"

#include "../Scene.h"

SceneManager::SceneManager() : dirty(false) {
    
}

void SceneManager::registerScene(std::string const& sceneId, std::shared_ptr<Scene> scene) {
    auto f = sceneMap.find(sceneId);
    if (f != sceneMap.end()) {
        throw std::runtime_error("SceneManager::registerScene: Scene id already used: " + sceneId);
    }
    sceneMap[sceneId] = scene;
}

void SceneManager::loadScene(std::string const& sceneId) {
    auto f = sceneMap.find(sceneId);
    if (f == sceneMap.end()) {
        throw std::runtime_error("SceneManager::loadScene: No scene found with id: " + sceneId);
    }
    if (currentScene != f->second) {
        dirty = true;
        currentScene = f->second;
    }
}

void SceneManager::makeClean() {
    dirty = false;
}