#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../utils/Shader.h"

class ShaderManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaderMap;
public:
    ShaderManager();

    Shader& loadShader(std::string const& shaderId, std::string const& vsPath, std::string const& fsPath);
    Shader& getShader(std::string const& shaderId) const;
};