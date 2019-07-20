#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoords;

uniform int time;
uniform float strength;

void main() {
    TexCoords = aTexCoord;
    gl_Position = vec4(aPos, 0.0f, 1.0f);

    gl_Position.x += (cos(time) * strength);
    gl_Position.y += (cos(time) * strength);

}
