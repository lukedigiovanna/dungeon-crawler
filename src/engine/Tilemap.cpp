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

const Tile EMPTY_TILE = Tile();

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
void addWallToChunk(Chunk& chunk, const math::vec2 ep1, const math::vec2 ep2, const math::vec2& center) {
    math::Wall wall;
    wall.ep1 = ep1;
    wall.ep2 = ep2;
    math::vec2 diff = wall.ep1 - wall.ep2;
    math::vec2 norm = { -diff.y, diff.x };
    if (math::dot(norm, wall.ep1 - center) < 0) {
        norm = norm * -1;
    }
    wall.normal = norm;
    chunk.occludingWalls.push_back(wall);
}

void Tilemap::recomputeOccludingWalls(int chunkRow, int chunkColumn) {
    if (chunkRow < 0 || chunkRow >= nChunksHeight || chunkColumn < 0 || chunkColumn >= nChunksWidth) {
        throw std::runtime_error("Tilemap::recomputeOccludingWalls: Chunk index out of bounds: " + std::to_string(chunkRow) + ", " + std::to_string(chunkColumn));
    }
    int cii = chunkRow * nChunksWidth + chunkColumn;
    Chunk& chunk = chunks[cii];
    chunk.occludingWalls.clear();
    for (int ti = 0; ti < CHUNK_SIZE; ti++) {
        for (int tj = 0; tj < CHUNK_SIZE; tj++) {
            int tii = chunkRow * CHUNK_SIZE + ti;
            int tjj = chunkColumn * CHUNK_SIZE + tj;
            int ii = tii * width + tjj;
            Tile& tile = tiles[ii];
            if (!tile.wall) 
                continue;

            float wx = getWorldX(tjj);
            float wy = getWorldY(tii);
            math::vec2 center = tile.getWallPolygon().center;
            // 4 cases:
            // Follow top wall
            // if (tii == 0 || !tiles[ii - width].wall) {
            //     int c = tii + 1;
            //     while (c - tii <)
            // }
            
            if (tii > 0 && !tiles[ii - width].wall) {
                addWallToChunk(chunk, { wx, wy }, { wx + scale, wy }, center);
            }
            if (tii < height - 1 && !tiles[ii + width].wall) {
                addWallToChunk(chunk, { wx, wy - scale }, { wx + scale, wy - scale }, center);
            }
            if (tjj > 0 && !tiles[ii - 1].wall) {
                addWallToChunk(chunk, { wx, wy }, { wx, wy - scale }, center);
            }
            if (tjj < width - 1 && !tiles[ii + 1].wall) {
                addWallToChunk(chunk, { wx + scale, wy }, { wx + scale, wy - scale }, center);
            }

            // if (tile.wall) {
            //     math::Polygon const& poly = tile.getWallPolygon();
            //     for (size_t i = 0; i < 4; i++) {
            //         math::Wall wall;
            //         wall.ep1 = poly.points[i];
            //         wall.ep2 = poly.points[(i + 1) % 4];
            //         math::vec2 diff = wall.ep1 - wall.ep2;
            //         math::vec2 norm = { -diff.y, diff.x };
            //         if (math::dot(norm, wall.ep1 - poly.center) < 0) {
            //             norm = norm * -1;
            //         }
            //         wall.normal = norm;
            //         chunk.occludingWalls.push_back(wall);
            //     }
            // }
        }
    }
}

void Tilemap::recomputeOccludingWalls() {
    for (int ci = 0; ci < nChunksHeight; ci++) {
        for (int cj = 0; cj < nChunksWidth; cj++) {
            recomputeOccludingWalls(ci, cj);
        }
    }
}

std::vector<math::Wall> EMPTY_WALLS;
std::vector<math::Wall> const& Tilemap::getOccludingWalls(int chunkRow, int chunkColumn) const {
    if (chunkRow < 0 || chunkRow >= nChunksHeight || chunkColumn < 0 || chunkColumn >= nChunksWidth) {
        return EMPTY_WALLS;
    }
    int cii = chunkRow * nChunksWidth + chunkColumn;
    return chunks[cii].occludingWalls;
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
    int row = getTileRow(y);
    int col = getTileColumn(x);
    if (row == -1 || col == -1) {
        return EMPTY_TILE; // Return the empty tile.
    }
    return getTile(row, col);
}

int Tilemap::getTileRow(float worldY) const {
    int row = static_cast<int>((worldHeight / 2.0f - worldY) / worldHeight * height);
    if (row < 0 || row >= height) {
        return -1;
    }
    return row;
}

int Tilemap::getTileColumn(float worldX) const { 
    int col = static_cast<int>((worldX + worldWidth / 2.0f) / worldWidth * width);
    if (col < 0 || col >= width) {
        return -1;
    }
    return col;
}

int Tilemap::getChunkRow(float worldY) const {
    int tileRow = getTileRow(worldY);
    return tileRow == -1 ? tileRow : tileRow / CHUNK_SIZE;
}

int Tilemap::getChunkColumn(float worldX) const {
    int tileColumn = getTileColumn(worldX);
    return tileColumn == -1 ? tileColumn : tileColumn / CHUNK_SIZE;
}

float Tilemap::getWorldY(int tileRow) const {
    return worldHeight / 2.0f - static_cast<float>(tileRow) / height * worldHeight;
}

float Tilemap::getWorldX(int tileColumn) const {
   return  static_cast<float>(tileColumn) / width * worldWidth - worldWidth / 2.0f;
}

void Tilemap::render(Shader const& shader, math::Rectangle const& viewport) const {
    std::shared_ptr<SpriteManager> spriteManager = getScene()->getManagers()->spriteManager;
    std::shared_ptr<ShaderManager> shaderManager = getScene()->getManagers()->shaderManager;
    Shader& tmShader = shaderManager->getShader("_tm_chunk");
    
    GLint currentViewport[4];
    glGetIntegerv(GL_VIEWPORT, currentViewport);

    int startColumn = getChunkColumn(viewport.x);
    int startRow = getChunkRow(viewport.y);
    int endColumn = getChunkColumn(viewport.x + viewport.width);
    endColumn = endColumn == -1 ? nChunksWidth - 1 : endColumn;
    int endRow = getChunkRow(viewport.y - viewport.height);
    endRow = endRow == -1 ? nChunksHeight - 1 : endRow;
    
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startColumn; j <= endColumn; j++) {
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