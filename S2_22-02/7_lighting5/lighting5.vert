#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 N;
out vec3 P;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform bool world;

void main()
{
    if (world) {
        P = vertex.xyz;
        N = normal;
    }
    else {
        P = (modelViewMatrix * vec4(vertex.xyz, 1.0)).xyz;
        N = normalMatrix * normal;
    }
   
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
}



