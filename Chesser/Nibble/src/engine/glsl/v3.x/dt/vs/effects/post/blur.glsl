#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out float vStrength;
out mat3 vKernel;

uniform float mStrength;
uniform mat3 mKernel;

void main() {
    TexCoord = aTexCoord;
    vStrength = mStrength;
    vKernel = mKernel;
    gl_Position = vec4(aPos, 1.0f, 1.0f); 
}
