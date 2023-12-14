#include "Tilemap.h"

#include "utils/meshes.h"
#include "Scene.h"

#include <queue>
#include <array>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Tile::Tile() : spriteId(-1), wall(false) {

}

Tile::Tile(float x, float y, float size) : Tile(-1, false, x, y, size) {
    
}

Tile::Tile(int spriteId, bool wall, float x, float y, float size) :
    spriteId(spriteId), wall(wall) {
    wallPolygon.center = { x + size / 2, y - size / 2 };
    wallPolygon.points = {
        { x, y },
        { x + size, y },
        { x + size, y - size },
        { x, y - size }
    };
}

math::Polygon const& Tile::getWallPolygon() const {
    return wallPolygon;
}

Tilemap::Tilemap(int width, int height, float scale) : scale(scale) {
    this->width = width;
    this->height = height;
    nChunksWidth = width / CHUNK_SIZE;
    nChunksHeight = height / CHUNK_SIZE;
    if (width % CHUNK_SIZE != 0) nChunksWidth++;
    if (height % CHUNK_SIZE != 0) nChunksHeight++;
    worldWidth = nChunksWidth * CHUNK_SIZE * scale;
    worldHeight = nChunksHeight * CHUNK_SIZE * scale;
    chunks = std::make_unique<Chunk[]>(nChunksWidth * nChunksHeight);
    for (int i = 0; i < nChunksWidth * nChunksHeight; i++) {
        chunks[i] = {
            .isDirty=true,
            .fb=Framebuffer(CHUNK_BUFFER_SIZE, CHUNK_BUFFER_SIZE)
        };
    }
    tiles = std::make_unique<Tile[]>(width * height);
    for (int i = 0; i < width * height; i++) {
        float x = static_cast<float>(i % width) / width * worldWidth - worldWidth / 2.0f;
        float y = worldHeight / 2.0f - static_cast<float>(i / width) / height * worldHeight;
        tiles[i] = Tile(x, y, scale);
    }
}

std::shared_ptr<Scene> Tilemap::getScene() const {
    std::shared_ptr<Scene> s = scene.lock();
    if (s == nullptr) {
        throw std::runtime_error("Tilemap::getScene: Cannot get the scene of a tilemap which is not attached to a scene");
    }
    return s;
}

void Tilemap::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}   

float Tilemap::getScale() const {
    return scale;
}

#include <iostream>
void Tilemap::recomputeWallPolygons() {
    walls.clear();
    auto seen = std::make_unique<bool[]>(width * height);
    // std::fill_n(seen.get(), width * height, false);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int ii = i * width + j;
            if (!tiles[ii].wall || seen[ii])
                continue;

            // execute a BFS to discover the entire wall section
            // std::vector<int> wall;
            // std::queue<int> q;
            // q.push(ii);
            // static std::array<std::pair<int, int>, 4> dirs{{
            //     {1, 0}, {-1, 0}, {0, 1}, {0, -1}
            // }};
            // while (q.size() > 0) {
            //     int ind = q.front();
            //     q.pop();
            //     wall.push_back(ind);
            //     int tj = ind % width, ti = ind / width;
            //     for (auto & dir : dirs) {
            //         int ni = ti + dir.first, nj = tj + dir.second;
            //         if (ni < 0 || ni >= height || nj < 0 || nj >= width)
            //             continue;
            //         int nii = ni * width + nj;
            //         if (!tiles[nii].wall || seen[nii]) 
            //             continue;
            //         seen[nii] = true;
            //         q.push(nii);
            //     }
            // }

            float x = static_cast<float>(j) / width * worldWidth - worldWidth / 2.0f;
            float y = worldHeight / 2.0f - static_cast<float>(i) / height * worldHeight;
            std::array<math::vec2, 4> corners{{
                {x, y}, {x + scale, y}, {x + scale, y - scale}, {x, y - scale}
            }};
            for (size_t i = 0; i < 4; i++) {
                math::Polygon p;
                p.points = std::vector<math::vec2>{corners[i], corners[(i + 1) % 4]};
                p.center = {x + scale / 2.0f, y - scale / 2.0f};
                walls.push_back(p);
            }
        }
    }
}

std::vector<math::Polygon> const& Tilemap::getWallPolygons() const {
    return walls;
}

void Tilemap::setTile(int row, int col, int spriteId, bool wall) {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        throw std::runtime_error("Tilemap::setTile: Coordinates out of bounds: row, col = " + std::to_string(row) + ", " + std::to_string(col));
    }
    int i = row * width + col;
    int cr = row / CHUNK_SIZE, cc = col / CHUNK_SIZE;
    int ci = cr * nChunksWidth + cc;
    if (spriteId != tiles[i].spriteId || wall != tiles[i].wall) {
        tiles[i].spriteId = spriteId;
        tiles[i].wall = wall;
        chunks[ci].isDirty = true;
    }
}

void Tilemap::setTileFromWorldPosition(float x, float y, int spriteId, bool wall) {
    // Convert x, y to row, pos
    int row = static_cast<int>((worldHeight / 2.0f - y) / worldHeight * height);
    int col = static_cast<int>((x + worldWidth / 2.0f) / worldWidth * width);
    if (row < 0 || row >= height || col < 0 || col >= width)
        return;
    setTile(row, col, spriteId, wall);
}

Tile const& Tilemap::getTile(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        throw std::runtime_error("Tilemap::getTile: Coordinates out of bounds: row, col = " + std::to_string(row) + ", " + std::to_string(col));
    }
    int i = row * width + col;
    return tiles[i];
}

Tile const& Tilemap::getTileFromWorldPosition(float x, float y) const {
    // Convert x, y to row, pos
    int row = static_cast<int>((worldHeight / 2.0f - y) / worldHeight * height);
    int col = static_cast<int>((x + worldWidth / 2.0f) / worldWidth * width);
    if (row < 0 || row >= height || col < 0 || col >= width) {}
        return Tile(); // Return the empty tile.
    return getTile(row, col);
}

void Tilemap::render(Shader const& shader) const {
    std::shared_ptr<SpriteManager> spriteManager = getScene()->getManagers()->spriteManager;
    std::shared_ptr<ShaderManager> shaderManager = getScene()->getManagers()->shaderManager;
    Shader& tmShader = shaderManager->getShader("_tm_chunk");
    
    GLint currentViewport[4];
    glGetIntegerv(GL_VIEWPORT, currentViewport);

    for (int i = 0; i < nChunksHeight; i++) {
        for (int j = 0; j < nChunksWidth; j++) {
            int ci = i * nChunksWidth + j;
            Chunk& chunk = chunks[ci];
            if (chunk.isDirty) {
                // Update this chunk's frame buffer
                chunk.fb.bindBuffer();
                tmShader.use();
                glViewport(0, 0, CHUNK_BUFFER_SIZE, CHUNK_BUFFER_SIZE);
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
                glClear(GL_COLOR_BUFFER_BIT);
                for (int ii = 0; ii < CHUNK_SIZE; ii++) {
                    int row = i * CHUNK_SIZE + ii;
                    if (row >= height) break; 
                    for (int jj = 0; jj < CHUNK_SIZE; jj++) {
                        int col = j * CHUNK_SIZE + jj;
                        if (col >= width) break;
                        int ti = row * width + col;
                        const Tile& tile = tiles[ti];
                        if (tile.spriteId < 0) 
                            continue;
                        const Sprite* sprite = spriteManager->getSpriteByIndex(tile.spriteId);
                        float x = static_cast<float>(jj) / CHUNK_SIZE * 2.0f - 1.0f;
                        float y = static_cast<float>(ii) / CHUNK_SIZE * 2.0f - 1.0f;
                        tmShader.setVec4("rect", glm::vec4(x, y, TILE_SIZE, TILE_SIZE));
                        sprite->render(tmShader);
                    }
                }
                
                chunk.fb.unbindBuffer();
                chunk.isDirty = false;
            }
            // render the chunk to the world
            shader.use();
            glViewport(currentViewport[0], currentViewport[1], currentViewport[2], currentViewport[3]);

            float y = static_cast<float>(nChunksHeight - i - 1) / nChunksHeight * worldHeight - worldHeight / 2.0f + CHUNK_SIZE * scale / 2.0f; 
            float x = static_cast<float>(j) / nChunksWidth * worldWidth - worldWidth / 2.0f + CHUNK_SIZE * scale / 2.0f; 
            glm::mat4 trans(1.0f);
            trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
            trans = glm::scale(trans, glm::vec3(scale * CHUNK_SIZE, scale * CHUNK_SIZE, 1.0f));
            shader.setMatrix4("model", trans);
            chunk.fb.bindTexture();
            shader.setVec4("objectColor", glm::vec4(1.0f));
            shader.setVec4("clipRect", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
            meshes::SQUARE->render();
        }
    }
}