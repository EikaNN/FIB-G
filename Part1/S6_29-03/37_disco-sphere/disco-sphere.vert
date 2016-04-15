#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 Veye;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{

    float phi = 0.1*time;

    mat3 Ry = mat3(
                    vec3(cos(phi), 0, -sin(phi)),
                    vec3(0, 1, 0),
                    vec3(sin(phi), 0, cos(phi))
                  );
    
    vec3 Vobj = Ry*vertex;

    vec4 Veye4 = modelViewMatrix*vec4(Vobj, 1);
    Veye = Veye4.xyz;

    gl_Position = projectionMatrix * Veye4;
}

