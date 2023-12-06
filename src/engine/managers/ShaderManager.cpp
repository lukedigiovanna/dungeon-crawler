#include "ShaderManager.h"

#include <iostream>
#include <utility>

ShaderManager::ShaderManager() {

}

Shader& ShaderManager::loadShader(std::string const& shaderId, std::string const& vsPath, std::string const& fsPath) {
    if (shaderMap.find(shaderId) != shaderMap.end()) {
        throw std::runtime_error("ShaderManager::loadShader: shader id '" + shaderId + "' is already used");
    }
    std::unique_ptr<Shader> shader = std::make_unique<Shader>(vsPath, fsPath);
    shaderMap[shaderId] = std::move(shader);
    return *shaderMap[shaderId];
}

Shader& ShaderManager::getShader(std::string const& shaderId) const {
    auto f = shaderMap.find(shaderId);
    if (f == shaderMap.end()) {
        throw std::runtime_error("ShaderManager::getShader: no shader found with id '" + shaderId + "'");
    }
    return *(f->second);
}