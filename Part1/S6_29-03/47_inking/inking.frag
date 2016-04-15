#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform int textureSize = 1024;
uniform int edgeSize = 2;
uniform float threshold = 0.1;
uniform sampler2D astronaut0;

const vec4 BLACK = vec4(0, 0, 0, 1);

void main()
{
    vec2 left = vtexCoord + edgeSize*vec2(-1, 0)/textureSize;
    vec2 right = vtexCoord + edgeSize*vec2(1, 0)/textureSize;
    vec2 bottom = vtexCoord + edgeSize*vec2(0, -1)/textureSize;
    vec2 top = vtexCoord + edgeSize*vec2(0, 1)/textureSize;

    float gx = length(texture(astronaut0, left) - texture(astronaut0, right));
    float gy = length(texture(astronaut0, top) - texture(astronaut0, bottom));

    if (length(vec2(gx, gy)) > threshold) fragColor = BLACK;
    else fragColor = texture(astronaut0, vtexCoord);
}
