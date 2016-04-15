#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{
    float phi = 0.4*vertex.y*sin(time);

    mat3 Ry = mat3(
                    vec3(cos(phi), 0, -sin(phi)),
                    vec3(0, 1, 0),
                    vec3(sin(phi), 0, cos(phi))
                  );
    
    vec3 Vobj = Ry*vertex;

    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(Vobj, 1.0);
}
