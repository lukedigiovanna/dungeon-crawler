#include "LightSource.h"

#include "../GameObject.h"
#include "../Scene.h"
#include "../utils/meshes.h"

#include <string>

unsigned int LightSource::vbo = 0;
unsigned int LightSource::vao = 0;
bool LightSource::initialized = false;

void LightSource::initializeVertexObject() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float data[12] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    initialized = true;
}

LightSource::LightSource(gfx::color const& color, float luminance) :
    color(color), luminance(luminance), shadowFBO(Framebuffer(100, 100)) {
    if (!initialized) {
        initializeVertexObject();
    }
}

void LightSource::set(Shader const& shader, int index, glm::mat4 const& projection) const {
    auto obj = getGameObject();
    auto scene = obj->getScene();
    shader.setFloat(("lights[" + std::to_string(index) + "].luminance").c_str(), luminance);
    shader.setVec3(("lights[" + std::to_string(index) + "].color").c_str(), color.r, color.g, color.b);
    shader.setVec2(("lights[" + std::to_string(index) + "].position").c_str(), obj->transform.position.x, obj->transform.position.y);
    
    GLint currentViewport[4];
    glGetIntegerv(GL_VIEWPORT, currentViewport);

    shadowFBO.bindBuffer();
    glViewport(0, 0, 100, 100);
    glClearColor(0.1f, 0.0f, 0.0f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    if (scene->hasTilemap()) {
        Shader& lightingShader = scene->getManagers()->shaderManager->getShader("_lighting");
        lightingShader.use();
        lightingShader.setMatrix4("projection", projection);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    shadowFBO.unbindBuffer();

    shader.use();   
    glViewport(currentViewport[0], currentViewport[1], currentViewport[2], currentViewport[3]);

    glActiveTexture(GL_TEXTURE1 + index);
    glBindTexture(GL_TEXTURE_2D, shadowFBO.getTexture());
    shader.setInt(("shadowMaps[" + std::to_string(index) + "]").c_str(), 1 + index);
}

void LightSource::update(float dt) {

}