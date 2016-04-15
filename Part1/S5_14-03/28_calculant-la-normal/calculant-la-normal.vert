#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec3 frontColor;
out vec4 fragVertex;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

void main()
{
    frontColor = color;
    fragVertex = modelViewMatrix * vec4(vertex, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
