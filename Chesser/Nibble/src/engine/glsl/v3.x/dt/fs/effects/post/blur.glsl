#version 330 core

in vec2 TexCoord;
in float vStrength;
in mat3 vKernel;

uniform sampler2D _tex;

layout(location = 0) out vec4 FragColor;

const float offset = 1.0 / 300.0;

void main() {
    vec2 offsets[9] = vec2[](
            vec2(-offset, offset), // top-left
            vec2(0.0f, offset), // top-center
            vec2(offset, offset), // top-right
            vec2(-offset, 0.0f), // center-left
            vec2(0.0f, 0.0f), // center-center
            vec2(offset, 0.0f ), // center-right
            vec2(-offset, -offset), // bottem-left
            vec2(0.0f, -offset), // bottom-center
            vec2(offset, -offset) // bottom-right
            );  

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(_tex, TexCoord.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++) 
        col += sampleTex[i] * vKernel[i];

    FragColor = vec4(col, 1.0);
}
