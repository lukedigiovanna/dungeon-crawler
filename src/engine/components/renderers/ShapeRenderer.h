#pragma once

#include "RendererComponent.h"
#include "../../utils/Graphics.h"
#include "../../utils/Mesh.h"

class ShapeRenderer: public RendererComponent {
private:
    const Mesh* mesh;
    gfx::color color;
public:
    ShapeRenderer(const Mesh* mesh, gfx::color color);
    ~ShapeRenderer();

    void render(std::shared_ptr<Shader> shader) const override;
};