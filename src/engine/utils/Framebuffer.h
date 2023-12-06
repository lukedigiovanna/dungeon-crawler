#pragma once

#include <glad/glad.h>

// Manages any custom frame buffer

class Framebuffer {
private:
    unsigned int fbo;
    unsigned int texture;
public:
    Framebuffer(GLsizei width, GLsizei height);
    Framebuffer();
    ~Framebuffer();

    void bindBuffer() const;
    void unbindBuffer() const;
    void bindTexture() const;

    inline unsigned int getTexture() const {
        return texture;
    }
};