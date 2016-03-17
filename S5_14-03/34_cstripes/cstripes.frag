#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 RED = vec4(1, 0, 0, 1);

uniform int nstripes = 16;
uniform vec2 origin = vec2(0,0);

void main()
{
    float l = length(vec2(vtexCoord.s,vtexCoord.t) - origin);
    
    if (mod(l*nstripes, 2) < 1) fragColor = RED;
    else fragColor = YELLOW;

}
