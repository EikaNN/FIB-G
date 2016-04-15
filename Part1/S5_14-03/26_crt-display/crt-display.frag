#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n;

void main()
{
    int y = int(floor(gl_FragCoord.y));
    if (mod(y, n) == 0) fragColor = frontColor;
    else discard;
    
}
