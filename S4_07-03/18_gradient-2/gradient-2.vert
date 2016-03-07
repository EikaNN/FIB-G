#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

void main()
{
    vec4 Pclip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    float y = 2.0*(Pclip.y/Pclip.w);

    vec3 red = vec3(1, 0, 0);
    vec3 green = vec3(0, 1, 0);
    vec3 blue = vec3(0, 0, 1);
    vec3 yellow = vec3(1, 1, 0);
    vec3 cyan = vec3(0, 1, 1);

    vec3 inter;
    if (y < -1) inter = mix(red, yellow, fract(y));
    else if (y < 0) inter = mix(yellow, green, fract(y));
    else if (y < 1) inter = mix(green, cyan, fract(y));
    else if (y < 2) inter = mix(cyan, blue, fract(y));
    else inter = blue;

    frontColor = vec4(inter, 1.0);
    vtexCoord = texCoord;

    gl_Position = Pclip;
}


