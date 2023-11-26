#version 330 core

uniform vec3 viewPosition;

in vec2 TexCoord;

in vec3 FragPos;

uniform sampler2D ourTexture;

uniform vec3 objectColor;

out vec4 FragColor;
void main() {
    // vec4 texColor = texture(ourTexture, TexCoord);

    // if (texColor.a < 0.1) 
    //     discard;

    // FragColor = texColor * vec4(objectColor, 1.0);
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}