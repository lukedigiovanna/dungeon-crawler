#pragma once

#include <glad/glad.h>

// Manages any custom frame buffer

class Framebuffer {
private:
    unsigned int fbo;
public:
    Framebuffer();
    ~Framebuffer();

    void bind() const;
    void unbind() const;
};