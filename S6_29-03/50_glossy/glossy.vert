#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 Peye;
out vec3 Neye;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{
    Neye = normalMatrix*normal;
    Peye = (modelViewMatrix*vec4(vertex, 1)).xyz;
    gl_Position = modelViewProjectionMatrix*vec4(vertex, 1);
}
