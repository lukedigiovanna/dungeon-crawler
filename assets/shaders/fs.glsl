#version 330 core

in vec2 TexCoord;
in vec2 FragPos; // 2D position in the world

struct Light {
    vec2 position;
    vec3 color;
    float luminance;
};

uniform sampler2D ourTexture;
uniform vec4 clipRect;

uniform vec4 objectColor;
uniform Light light;

out vec4 FragColor;
void main() {
    // transform the texture coord to be relative to the clip rect
    vec2 transformedTexCoord = clipRect.xy + vec2(TexCoord.x, 1.0 - TexCoord.y) * clipRect.zw;
    vec4 texColor = texture(ourTexture, transformedTexCoord);

    if (texColor.a < 0.1) 
        discard;

    // Light calculations
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / dist; // Simple distance-based attenuation
    vec3 lightEffect = light.color * light.luminance * attenuation;

    FragColor = texColor * objectColor * vec4(lightEffect, 1.0);
}