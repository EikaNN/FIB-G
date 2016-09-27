#version 330 core

in vec3 gnormal;
out vec4 fragColor;

const vec4 GREY = vec4(vec3(0.8), 1);

uniform mat3 normalMatrix;

void main()
{
    vec3 Neye = normalize(normalMatrix*gnormal); 
    fragColor = GREY*Neye.z;
}
