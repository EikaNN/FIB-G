#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat4 projectionMatrix;

const vec4 RED = vec4(1, 0, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);
const float areamax = 0.0005;

vec4 getColor(vec3 V0, vec3 V1, vec3 V2)
{
    vec3 u = V2 - V0;
    vec3 v = V1 - V0;
    float area =  length(cross(u, v))/2;
    area /= areamax;
    vec4 color = mix(RED, YELLOW, area);
    if (area >= 1.0) color = YELLOW;
    return color;
}

void emitVertex(vec3 V, vec4 color)
{
    gl_Position = projectionMatrix*vec4(V, 1.0);
    gfrontColor = color;
    EmitVertex();
}

void main( void )
{
    vec3 V0 = gl_in[0].gl_Position.xyz;
    vec3 V1 = gl_in[1].gl_Position.xyz;
    vec3 V2 = gl_in[2].gl_Position.xyz;
    vec4 color = getColor(V0, V1, V2);
    emitVertex(V0, color);
    emitVertex(V1, color);
    emitVertex(V2, color);
    EndPrimitive();
}


