#version 330 core

in vec3 Neye;
in vec3 Peye;
in vec4 frontColor;
out vec4 fragColor;

uniform float epsilon = 0.1;
uniform float light = 0.5;

const vec4 DARK_YELLOW = vec4(0.7, 0.6, 0.0, 1.0); 

void main()
{
    vec3 N = normalize(Neye);
    vec3 P = normalize(Peye);
    float prod = dot(P, N);
    if (abs(prod) < epsilon) fragColor = DARK_YELLOW;
    else fragColor = frontColor*light*N.z;
}

