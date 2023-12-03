#include "Framebuffer.h"

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &fbo);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &fbo);
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Framebuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}