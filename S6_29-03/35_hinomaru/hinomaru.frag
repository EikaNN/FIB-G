#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec4 RED = vec4(1, 0, 0, 1);
const vec4 WHITE = vec4(1, 1, 1, 1);

float aastep(float threshold, float x)
{
    float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
    return smoothstep(threshold-width, threshold+width, x);
}


void main()
{
    vec2 center = vec2(0.5, 0.5);
    float d = distance(vtexCoord, center);
    fragColor = vec4(1, step(0.2, d), step(0.2, d), 1);
    // Fem servir el aastep
    //fragColor = vec4(1, aastep(0.2, d), aastep(0.2, d), 1);
}
