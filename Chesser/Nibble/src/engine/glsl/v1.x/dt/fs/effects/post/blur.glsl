#version 100
precision mediump float;

varying vec2 TexCoord;
varying float vStrength;
varyint mat3 vKernel;

uniform sampler2D _tex;

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
        sampleTex[i] = vec3(texture2D(_tex, TexCoord.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++) 
        col += sampleTex[i] * vKernel[i];

    gl_FragColor = vec4(col, 1.0);

}
