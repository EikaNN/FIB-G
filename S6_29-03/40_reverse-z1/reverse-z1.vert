#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

void main()
{
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    
    vec4 Pclip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    Pclip.z = -Pclip.z;
    gl_Position = Pclip;
}
