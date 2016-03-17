#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

const vec4 GREY = vec4(vec3(0.8), 1);
const vec4 BLACK = vec4(vec3(0), 1);

void main()
{
    float s = floor(vtexCoord.s * n);
    float t = floor(vtexCoord.t * n);
    int x = int(mod(s, 2));
    int y = int(mod(t, 2));
    if (x == y) fragColor = GREY;
    else fragColor = BLACK;
}
