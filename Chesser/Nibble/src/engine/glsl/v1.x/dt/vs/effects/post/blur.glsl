#version 100
precision mediump float;

attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTexCoord;

varying vec3 vsColor;
varying vec2 TexCoord;
varying mat3 vKernel;

uniform float mStrength;
uniform mat3 vKernel;

void main() {
    vsColor = aColor;
    TexCord = aTexCord;
    vStrength = mStrength;
    gl_Position = aPos;
}
