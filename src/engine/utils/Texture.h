#pragma once

#include "Shader.h"

#include <string>

class Texture {
private:
    int width, height, nrChannels;
    unsigned int texture;
public:
    /* DANGEROUS */
    Texture(); // default constructor leaves everything uninitialized

    Texture(std::string const& imagePath);
    ~Texture();

    void bind() const;
    void bind(Shader const& shader, std::string const& uniformName) const;
    void unbind() const;
};
