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

#define MAX_NUM_LIGHTS 64
uniform int numLights;
uniform Light[MAX_NUM_LIGHTS] lights;

uniform vec3 ambientLight;

out vec4 FragColor;
void main() {
    // transform the texture coord to be relative to the clip rect
    vec2 transformedTexCoord = clipRect.xy + vec2(TexCoord.x, 1.0 - TexCoord.y) * clipRect.zw;
    vec4 texColor = texture(ourTexture, transformedTexCoord);

    if (texColor.a < 0.1) 
        discard;

    // Light calculations
    vec3 lightEffect = ambientLight;
    for (int i = 0; i < numLights; i++) {
        Light light = lights[i];
        float dist = length(light.position - FragPos);
        float attenuation = min(1.0, 1.0 / (dist * 0.75 + 0.6)); // Simple distance-based attenuation
        lightEffect += light.color * light.luminance * attenuation;
    }

    FragColor = texColor * objectColor * vec4(lightEffect, 1.0);
}