#include "LightSource.h"

#include "../GameObject.h"
#include "../Scene.h"
#include "../Engine.h"
#include "../utils/meshes.h"

#include <string>

unsigned int LightSource::vbo = 0;
unsigned int LightSource::vao = 0;
bool LightSource::initialized = false;

#define SHADOW_MAP_SIZE 2048

#define MAX_NUM_SHADOWS 500

void LightSource::initializeVertexObject() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float data[12 * MAX_NUM_SHADOWS];
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (12 * MAX_NUM_SHADOWS), data, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    initialized = true;
}

LightSource::LightSource(gfx::color const& color, float luminance) :
    color(color), luminance(luminance), shadowFBO(Framebuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE)) {
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

    shadowFBO.bindBuffer();
    
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    if (scene->hasTilemap()) {
        Shader& lightingShader = Engine::getSingleton()->getManagers()->shaderManager->getShader("_lighting");
        lightingShader.use();
        lightingShader.setMatrix4("projection", projection);
        
        Tilemap& tilemap = scene->getTilemap();

        int chunkRow = tilemap.getChunkRow(obj->transform.position.y);
        int chunkColumn = tilemap.getChunkColumn(obj->transform.position.x);
        int radius = 1;
        float shadowMeshData[12 * MAX_NUM_SHADOWS];
        int shadowIndex = 0;
        for (int dr = -radius; dr <= radius; dr++) {
            for (int dc = -radius; dc <= radius; dc++) {
                auto walls = scene->getTilemap().getOccludingWalls(chunkRow + dr, chunkColumn + dc);
        
                for (auto & wall : walls) {
                    math::vec2 ep1 = wall.ep1;
                    math::vec2 ep2 = wall.ep2;
                    math::vec2 dir = obj->transform.position - ep1;
                    if (math::dot(wall.normal, dir) < 0) 
                        continue;
                    math::vec2 dir1 = (ep1 - obj->transform.position).normalized() * 30, 
                                dir2 = (ep2 - obj->transform.position).normalized() * 30;
                    float vertices[12] = {
                        ep1.x, ep1.y,
                        ep2.x, ep2.y,
                        ep1.x + dir1.x, ep1.y + dir1.y,

                        ep1.x + dir1.x, ep1.y + dir1.y,
                        ep2.x, ep2.y,
                        ep2.x + dir2.x, ep2.y + dir2.y,
                    };
                    for (size_t i = 0; i < 12; i++) {
                        shadowMeshData[shadowIndex * 12 + i] = vertices[i];
                    }
                    shadowIndex++;

                    if (shadowIndex >= MAX_NUM_SHADOWS) {
                        goto render;
                    }
                }
            }
        }
    
render:

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * (12 * shadowIndex), shadowMeshData);
        glDrawArrays(GL_TRIANGLES, 0, 6 * shadowIndex);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    shadowFBO.unbindBuffer();

    shader.use();   

    glActiveTexture(GL_TEXTURE1 + index);
    glBindTexture(GL_TEXTURE_2D, shadowFBO.getTexture());
    shader.setInt(("shadowMaps[" + std::to_string(index) + "]").c_str(), 1 + index);
}

void LightSource::update(float dt) {

}