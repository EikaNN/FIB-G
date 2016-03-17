#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

const vec4 RED = vec4(1, 0, 0, 1);

bool isRed(float x) {
    return fract(x) < 0.1;
}

void main()
{
    float s = vtexCoord.s * n;
    float t = vtexCoord.t * n;
    if (isRed(s) || isRed(t)) fragColor = RED;
    else discard;
}
