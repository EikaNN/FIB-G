#version 330 core

in vec3 Neye;
in vec3 frontColor;
out vec4 fragColor;

void main()
{
    vec3 N = normalize(Neye);
    fragColor = vec4(frontColor, 1.0) * N.z;
}
