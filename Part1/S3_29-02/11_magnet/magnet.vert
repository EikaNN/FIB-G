#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat3 normalMatrix;
uniform vec4 lightPosition;

uniform float n = 4;

void main()
{
    vec4 Vobj = vec4(vertex, 1.0);
    vec4 Fobj = modelViewMatrixInverse*lightPosition;
    float d = distance(Vobj, Fobj);
    float w = clamp(1.0/pow(d, n), 0, 1);
    vec4 V = (1.0-w)*Vobj + w*Fobj;
    
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);

    gl_Position = modelViewProjectionMatrix * V;
}
