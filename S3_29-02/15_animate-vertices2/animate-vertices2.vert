#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1.0;
uniform float time;

const float PI = 3.14159;

void main()
{
    
    vec3 Neye = normalize(normalMatrix*normal);            
    vec4 Peye = modelViewMatrix*vec4(vertex.xyz, 1.0);

    frontColor = vec4(Neye.z); 
    
    Neye = Neye*amplitude*sin(2*PI*freq*time + 2*PI*texCoord.s);
    mat4 T = mat4(
                vec4(1.0, 0.0, 0.0, 0.0),
                vec4(0.0, 1.0, 0.0, 0.0),
                vec4(0.0, 0.0, 1.0, 0.0),
                vec4(Neye.x, Neye.y, Neye.z, 1.0)
             );
        
    Peye = T*Peye;

    gl_Position = projectionMatrix * Peye;
}

