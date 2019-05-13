attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTexCoord;

varying vec3 vsColor;
varying vec2 TexCoord;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    vsColor = aColor;
}