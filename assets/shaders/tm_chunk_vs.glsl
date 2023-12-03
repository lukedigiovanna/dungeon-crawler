#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoord;

uniform vec4 rect;

out vec2 TexCoord;

void main() {
    vec2 pos = rect.xy + (inPos + vec2(0.5, 0.5)) * rect.zw;
    gl_Position = vec4(pos, 0.0, 1.0);

    TexCoord = inTexCoord;
}