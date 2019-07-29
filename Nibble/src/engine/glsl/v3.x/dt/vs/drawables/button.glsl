#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 0.0f, 1.0f);
    TexCoord = aTexCoord;
}
