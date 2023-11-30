#version 330 core

in vec2 TexCoord;

in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec4 clipRect;

uniform vec4 objectColor;

out vec4 FragColor;
void main() {
    // transform the texture coord to be relative to the clip rect
    vec2 transformedTexCoord = clipRect.xy + TexCoord * clipRect.zw;
    vec4 texColor = texture(ourTexture, transformedTexCoord);

    if (texColor.a < 0.1) 
        discard;

    FragColor = texColor * objectColor;
}