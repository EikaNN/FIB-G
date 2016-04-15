#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

out vec4 Pobj;
out vec3 Nobj;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    Pobj = vec4(vertex, 1);
    Nobj = normal;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
