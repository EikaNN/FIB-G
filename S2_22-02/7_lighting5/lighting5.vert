#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;

out vec3 Nworld;
out vec3 Vworld;
out vec3 Lworld;

out vec3 Neye;
out vec3 Veye;
out vec3 Leye;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrixInverse;

uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space

void main()
{
    vec3 Pworld = vertex.xyz;
    Nworld = normal;   
    Vworld = (modelViewMatrixInverse[3]).xyz - Pworld;
    Lworld = (modelViewMatrixInverse*lightPosition).xyz - Pworld;
    
    vec3 Peye = (modelViewMatrix * vec4(vertex.xyz, 1.0)).xyz; 
    Neye = normalMatrix * normal;
    Leye = lightPosition.xyz - Peye;
    Veye = - Peye;

    vtexCoord = texCoord;
   
    gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
}



