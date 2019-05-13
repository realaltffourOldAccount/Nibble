precision mediump float;

varying vec3 vsColor;
varying vec2 TexCoord;

uniform sampler2D t_tex;

void main() { gl_FragColor = texture2D(t_tex, TexCoord); }