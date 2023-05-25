#version 330 core

in vec2 fTex;

uniform sampler2D ourTexture;

out vec4 outCol;

void main()
{
    outCol = texture(ourTexture, fTex);
}