#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../utils/Shader.h"

class ShaderManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;
public:
    ShaderManager();

    std::shared_ptr<Shader> loadShader(std::string const& shaderId, std::string const& vsPath, std::string const& fsPath);
    std::shared_ptr<Shader> getShader(std::string const& shaderId) const;
};