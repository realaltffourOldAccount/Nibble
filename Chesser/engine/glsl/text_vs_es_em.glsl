precision mediump float;
attribute vec4 vertex; // <vec2 pos, vec2 tex>

varying vec2 TexCoords;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}  