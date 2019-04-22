#version 330 core
out vec4 FragColor;

in vec3 outColour;
in vec2 TexCoord;

uniform sampler2D _tex;

void main () {
    FragColor = texture(_tex, TexCoord);
}