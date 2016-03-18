#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

uniform bool eyespace;
uniform float time;

const float PI = 3.14159;

void main()
{

    float r = distance(boundingBoxMin, boundingBoxMax) / 2.0;

    float y = vertex.y;
    if (eyespace) {
        vec4 row1 = vec4(modelViewMatrix[0][1], 
                        modelViewMatrix[1][1], 
                        modelViewMatrix[2][1], 
                        modelViewMatrix[3][1]
                    );
        y = dot(row1, vec4(vertex, 1.0));
    }
    

    vec3 N = normal * (r/10)*y * sin(time);

    mat4 T = mat4(  
                    vec4(1, 0, 0, 0),
                    vec4(0, 1, 0, 0),
                    vec4(0, 0, 1, 0),
                    vec4(N.x, N.y, N.z, 1)
                 );

    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * T * vec4(vertex, 1.0);
}
