#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{
    float phi = -time*texCoord.s;  
    mat3 Ry = mat3(
                    vec3(cos(phi), 0, -sin(phi)), 
                    vec3(0, 1, 0),
                    vec3(sin(phi), 0, cos(phi))
            );
    
    frontColor = vec4(0, 0, 1, 1);

    vtexCoord = texCoord;
    //vec3 vertexA = R * vertex;
    gl_Position = modelViewProjectionMatrix * vec4(Ry*vertex, 1.0);
}
