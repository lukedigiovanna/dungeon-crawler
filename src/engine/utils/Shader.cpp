#include "Shader.h"

#include "io.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int compileShader(std::string const& filepath, int shaderType) {
    std::string src = read_file(filepath);
    const char* c_src = src.c_str();
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &c_src, NULL);
    glCompileShader(shader);
    // Check for compile errors.
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR creating shader: " << filepath << std::endl;
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

#include <iostream>

Shader::Shader(std::string const& vsPath, std::string const& fsPath) {
    unsigned int vertexShader = compileShader(vsPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fsPath, GL_FRAGMENT_SHADER);
    // make the program
    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR linking shader: " << vsPath << ", " << fsPath << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(this->program);
}

void Shader::use() const {
    glUseProgram(this->program);
}

void Shader::setFloat(const char* uniformName, float v0) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniform1f(loc, v0);
}

void Shader::setInt(const char* uniformName, int i0) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniform1i(loc, i0);
}

void Shader::setVec2(const char* uniformName, float v0, float v1) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniform2f(loc, v0, v1);
}

void Shader::setVec3(const char* uniformName, float v0, float v1, float v2) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniform3f(loc, v0, v1, v2);
}

void Shader::setVec3(const char* uniformName, glm::vec3 vec) const {
    this->setVec3(uniformName, vec.x, vec.y, vec.z);
}

void Shader::setVec4(const char* uniformName, float v0, float v1, float v2, float v3) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniform4f(loc, v0, v1, v2, v3);
}

void Shader::setVec4(const char* uniformName, glm::vec4 vec) const {
    this->setVec4(uniformName, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMatrix4(const char* uniformName, const glm::mat4& matrix) const {
    unsigned int loc = glGetUniformLocation(this->program, uniformName);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}