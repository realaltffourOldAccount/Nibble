#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D _tex;

const float offset = 1.0 / 300.0;

void main() {
    color = vec4(0.0f);

    float kernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 2.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
            );

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

    vec3 sample[9];
    // sample from texture offsets 
    for(int i = 0; i < 9; i++)
        sample[i] = vec3(texture(_tex, TexCoords.st + offsets[i]));

    for (int i = 0; i < 9; i++)
        color += vec4(sample[i] * kernel[i], 0.0f);
    color.a = 1.0f;

}
