#version 330 core

in vec3 Neye;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D window;
uniform sampler2D interior1;
uniform sampler2D exterior2;

void main()
{
    vec4 colorC = texture(window, vtexCoord);
    if (colorC.a == 1) fragColor = colorC;
    else {
        vec2 auxD = vtexCoord + 0.5*Neye.xy;
        vec4 colorD = texture(interior1, auxD);
        if (colorD.a == 1) fragColor = colorD;
        else fragColor = texture(exterior2, vtexCoord + 0.7*Neye.xy);
    }
}
