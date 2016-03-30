#version 330 core

in vec4 frontColor;
in vec4 Pclip;
out vec4 fragColor;

void main()
{
    fragColor = frontColor;
    gl_FragDepth = 1 - gl_FragCoord.z;
}

