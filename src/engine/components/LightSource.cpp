#include "LightSource.h"

#include "../GameObject.h"
#include "../Scene.h"

#include <string>

LightSource::LightSource(gfx::color const& color, float luminance) :
    color(color), luminance(luminance), shadowFBO(Framebuffer(100, 100)) {

}

void LightSource::set(Shader const& shader, int index) const {
    auto obj = getGameObject();
    shader.setFloat(("lights[" + std::to_string(index) + "].luminance").c_str(), luminance);
    shader.setVec3(("lights[" + std::to_string(index) + "].color").c_str(), color.r, color.g, color.b);
    shader.setVec2(("lights[" + std::to_string(index) + "].position").c_str(), obj->transform.position.x, obj->transform.position.y);
    glActiveTexture(GL_TEXTURE1 + index);
    glBindTexture(GL_TEXTURE_2D, shadowFBO.getTexture());
    shader.setInt(("shadowMaps[" + std::to_string(index) + "]").c_str(), 1 + index);
}

void LightSource::update(float dt) {
    // Need to render to the thing
    auto obj = getGameObject();
    auto scene = obj->getScene();
    shadowFBO.bindBuffer();
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    if (scene->hasTilemap()) {
        
    }
    shadowFBO.unbindBuffer();
}