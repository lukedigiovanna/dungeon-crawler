#version 330 core
in vec2 TexCoord;
out vec4 outColor;

uniform sampler2D ourTexture;
uniform vec4 clipRect;
uniform vec4 color;

void main() {
    vec2 transformedTexCoord = clipRect.xy + vec2(TexCoord.x, 1.0 - TexCoord.y) * clipRect.zw;
    vec4 sampled = texture(ourTexture, transformedTexCoord);

    if (sampled.a < 0.1)
        discard;
    
    outColor = color * sampled;
}
