#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 Neye;
out vec3 Peye;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec4 Peye4 = modelViewMatrix * vec4(vertex.xyz, 1.0);
    Peye = Peye4.xyz;
    Neye = normalMatrix * normal;
    gl_Position = projectionMatrix * Peye4;
}
