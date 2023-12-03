#include "ShaderManager.h"

#include <iostream>

ShaderManager::ShaderManager() {

}

std::shared_ptr<Shader> ShaderManager::loadShader(std::string const& shaderId, std::string const& vsPath, std::string const& fsPath) {
    if (shaderMap.find(shaderId) != shaderMap.end()) {
        throw std::runtime_error("ShaderManager::loadShader: shader id '" + shaderId + "' is already used");
    }
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vsPath, fsPath);
    shaderMap[shaderId] = shader;
    return shader;
}

std::shared_ptr<Shader> ShaderManager::getShader(std::string const& shaderId) const {
    auto f = shaderMap.find(shaderId);
    if (f == shaderMap.end()) {
        throw std::runtime_error("ShaderManager::getShader: no shader found with id '" + shaderId + "'");
    }
    return f->second;
}