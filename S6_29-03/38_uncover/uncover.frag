#version 330 core

in vec4 Pclip;
out vec4 fragColor;

uniform float time;

const vec4 BLUE = vec4(0, 0, 1, 1);

void main()
{
    float d = Pclip.x / Pclip.w + 1.0;
    if (d <= time) fragColor = BLUE;
    else discard;
}
