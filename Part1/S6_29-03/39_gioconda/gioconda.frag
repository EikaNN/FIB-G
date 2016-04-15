#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler0;
uniform float time;

const vec2 ULL = vec2(0.393, 0.652);
const vec2 OFFSET = vec2(0.057, -0.172); 
const float RADI = 0.025;

void main()
{
    if (fract(time) <= 0.5) fragColor = texture(sampler0, vtexCoord);
    else {
        vec2 ftexCoord = vtexCoord;
        if (distance(vtexCoord, ULL) < RADI) {
            ftexCoord += OFFSET;
        }
        fragColor = texture(sampler0,ftexCoord);
    }
}
