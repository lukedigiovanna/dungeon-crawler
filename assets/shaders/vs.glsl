#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 pos = projection * view * model * vec4(inPos.xy, 0.0, 1.0);

    gl_Position = pos;

    TexCoord = inTexCoord;
    FragPos = vec3(vec4(inPos, 0.0, 1.0));
}