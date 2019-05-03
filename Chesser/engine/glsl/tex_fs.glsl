#version 330 core

in vec3 vsColor;
in vec2 TexCoord;

uniform sampler2D _tex;

layout (location = 0) out vec4 FragColor;

void main () {
    FragColor = texture(_tex, TexCoord);
}