#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform bool eyespace;
uniform float time;

uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

const float PI = 3.14159;

void main()
{

    float r = distance(boundingBoxMin, boundingBoxMax) / 2.0;

    float y = vertex.y;
    if (eyespace) {
        vec4 row = vec4(modelViewMatrix[0][1], 
                        modelViewMatrix[1][1], 
                        modelViewMatrix[2][1], 
                        modelViewMatrix[3][1]
                    );
        y = dot(row, vec4(vertex, 1.0));
    }
    
    
  //if (eyespace) y=(modelViewMatrix*vec4(vertex, 1)).y;

    vec3 N = normal * (r/10)*y * sin(time);

    mat4 T = mat4(  
                    vec4(1, 0, 0, 0),
                    vec4(0, 1, 0, 0),
                    vec4(0, 0, 1, 0),
                    vec4(N.x, N.y, N.z, 1)
                 );

    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * T * vec4(vertex, 1.0);
}
