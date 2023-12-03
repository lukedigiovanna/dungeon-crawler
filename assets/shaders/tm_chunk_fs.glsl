#version 330 core

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 clipRect;

out vec4 FragColor;
void main() {
    vec2 transformedTexCoord = clipRect.xy + vec2(TexCoord.x, TexCoord.y) * clipRect.zw;
    vec4 texColor = texture(ourTexture, transformedTexCoord);

    if (texColor.a < 0.1) 
        discard;

    FragColor = texColor;
}