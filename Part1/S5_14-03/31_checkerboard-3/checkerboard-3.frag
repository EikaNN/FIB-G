#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

const vec4 GREY = vec4(vec3(0.8), 1);
const vec4 BLACK = vec4(vec3(0), 1);

bool isBlack(float x) {
    return fract(x) < 0.1;
}

void main()
{
    float s = vtexCoord.s * n;
    float t = vtexCoord.t * n;
    if (isBlack(s) || isBlack(t)) fragColor = BLACK;
    else fragColor = GREY;
}
