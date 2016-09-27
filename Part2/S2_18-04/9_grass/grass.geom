#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vnormal[];
out vec3 gnormal;
out vec3 gPos;

uniform mat4 modelViewProjectionMatrix;
uniform float d = 0.1;

const vec4 GREY = vec4(vec3(0.8), 1);

void prismVertex(vec3 V, vec3 N) 
{
    gnormal = N;
    gPos = V;
    gl_Position = modelViewProjectionMatrix*vec4(V, 1);
    EmitVertex();
}

vec3 getNormal(vec3 A, vec3 B, vec3 C)
{
    vec3 u = B-A;
    vec3 v = C-A;
    return normalize(cross(u, v));
}

void paintPrism(vec3 N) 
{
    vec3 V0 = gl_in[0].gl_Position.xyz;
    vec3 V1 = gl_in[1].gl_Position.xyz;
    vec3 V2 = gl_in[2].gl_Position.xyz;
    vec3 V0p = V0 + d*N;
    vec3 V1p = V1 + d*N;
    vec3 V2p = V2 + d*N;

    // bottom
    vec3 n = N;
    prismVertex(V0, n);
    prismVertex(V2, n);
    prismVertex(V1, n);
    EndPrimitive();

    // back
    n = getNormal(V1, V2, V1p);
    prismVertex(V1, n);
    prismVertex(V2, n);
    prismVertex(V1p, n);
    prismVertex(V2p, n);
    EndPrimitive();

    // right
    n = getNormal(V0, V0p, V1);
    prismVertex(V0, n);
    prismVertex(V1, n);
    prismVertex(V0p, n);
    prismVertex(V1p, n);
    EndPrimitive();

    // left
    n = getNormal(V0, V0p, V2);
    prismVertex(V0, n);
    prismVertex(V0p, n);
    prismVertex(V2, n);
    prismVertex(V2p, n);
    EndPrimitive();
}

void main( void )
{
    vec3 N = (normalize(vnormal[0]) + normalize(vnormal[1]) + normalize(vnormal[2]))/3;
	paintPrism(normalize(N));
}

