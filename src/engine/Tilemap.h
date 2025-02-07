#pragma once

#include "utils/Shader.h"
#include "utils/Framebuffer.h"
#include "utils/Math.h"

#include <memory>

class Tile {
private:
    math::Polygon wallPolygon;
public:
    int spriteId; // -1 for empty
    bool wall;
    Tile(int spriteId, bool wall, float x, float y, float size);
    Tile(float x, float y, float size);
    Tile();

    math::Polygon const& getWallPolygon() const;
};

#define CHUNK_SIZE 16
#define CHUNK_BUFFER_SIZE 512
#define TILE_SIZE (2.0f / CHUNK_SIZE)

struct Chunk {
    bool isDirty;
    Framebuffer fb;
    std::vector<math::Wall> occludingWalls;
};

class Scene; // forward declare

class Tilemap {
private:
    int width, height;
    int nChunksWidth, nChunksHeight;
    float scale;
    float worldWidth, worldHeight;
    // Keeps track of all tile values
    // When a tile is made into a wall, changes are not reflected until 
    // occluding walls are recomputed via `recomputeOccludingWalls()`
    std::unique_ptr<Tile[]> tiles;
    // Keeps track of walls and prerendered framebuffers
    std::unique_ptr<Chunk[]> chunks;
    
    std::weak_ptr<Scene> scene;
public:
    Tilemap(int width, int height, float scale);
    /*
    Load a tilemap from a CSV file
    */
    Tilemap(const std::string& path, int spriteOffsetId, float scale);

    std::shared_ptr<Scene> getScene() const;
    void setScene(std::shared_ptr<Scene> scene);

    float getScale() const;

    void recomputeOccludingWalls();
    void recomputeOccludingWalls(int chunkRow, int chunkColumn);
    std::vector<math::Wall> const& getOccludingWalls(int chunkRow, int chunkColumn) const;

    void setTile(int row, int col, int spriteId, bool wall);
    void setTileFromWorldPosition(float x, float y, int spriteId, bool wall);

    Tile const& getTile(int row, int col) const;
    Tile const& getTileFromWorldPosition(float x, float y) const; 

    int getTileRow(float worldY) const;
    int getTileColumn(float worldX) const;
    int getChunkRow(float worldY) const;
    int getChunkColumn(float worldX) const;
    float getWorldY(int tileRow) const;
    float getWorldX(int tileColumn) const;

    void render(Shader const& shader, math::Rectangle const& viewport) const;

    inline int getWidth() const {
        return this->width;
    }

    inline int getHeight() const {
        return this->height;
    }
};