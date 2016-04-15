#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 Neye;
out vec3 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    Neye = normalMatrix*normal;
    frontColor = color;
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
}
