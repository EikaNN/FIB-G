#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 RED = vec4(1, 0, 0, 1);
const float a = 1.0/9.0;

void main()
{
    float s = fract(vtexCoord.s) * 1/a;
    if (mod(s, 2.0) < 1) fragColor = YELLOW;
    else fragColor = RED;
}

