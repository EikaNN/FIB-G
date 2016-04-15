#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float scale = 8;
uniform float time;

float triangleWave(float x) {
    return abs(mod(x, 2) - 1.0);
}


void main()
{

    vec3 T0 = vec3(-1, -1, 0);
    vec3 V = vec3(2, 2, 0);
    vec3 t = vec3(triangleWave(time/1.618), triangleWave(time), 0);

    mat4 T = mat4(
                    vec4(1, 0, 0, 0),
                    vec4(0, 1, 0, 0),
                    vec4(0, 0, 1, 0),    
                    vec4(scale*(T0 + V*t), 1)
                 );

    mat4 R = mat4(
                    vec4(1/scale, 0, 0, 0),
                    vec4(0, 1/scale, 0, 0),
                    vec4(0, 0, 1/scale, 0),    
                    vec4(0, 0, 0, 1)
                 );

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.3, 0.3, 0.9, 1.0) * N.z;
    gl_Position = modelViewProjectionMatrix * R*T * vec4(vertex, 1.0);
}
