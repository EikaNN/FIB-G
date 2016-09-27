#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out float gtop;
out vec3 gnormal;
out vec2 gtexCoord;
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.2;

void cubeVertex(float x, float y, float z, vec3 BT, vec3 N, bool isTop) {
    gtop = isTop ? 1 : 0;
    gtexCoord = vec2(z, x);
    gfrontColor = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2])/3;
    gnormal = N;
    vec3 V = vec3(x, y, z)*step;
    gl_Position = modelViewProjectionMatrix*vec4(V + BT, 1);
    EmitVertex();
}

void paintCube(vec3 BT) {
    // front
    vec3 N = normalMatrix*vec3(0, 0, -1);
    cubeVertex(0, 0, 0, BT, N, false);
    cubeVertex(1, 0, 0, BT, N, false);
    cubeVertex(0, 1, 0, BT, N, false);
    cubeVertex(1, 1, 0, BT, N, false);
    EndPrimitive();
    // back
    N = normalMatrix*vec3(0, 0, 1);
    cubeVertex(0, 0, 1, BT, N, false);
    cubeVertex(1, 0, 1, BT, N, false);
    cubeVertex(0, 1, 1, BT, N, false);
    cubeVertex(1, 1, 1, BT, N, false);
    EndPrimitive();
    // left
    N = normalMatrix*vec3(-1, 0, 0);
    cubeVertex(0, 0, 0, BT, N, false);
    cubeVertex(0, 0, 1, BT, N, false);
    cubeVertex(0, 1, 0, BT, N, false);
    cubeVertex(0, 1, 1, BT, N, false);
    EndPrimitive();
    // right
    N = normalMatrix*vec3(1, 0, 0);
    cubeVertex(1, 0, 0, BT, N, false);
    cubeVertex(1, 0, 1, BT, N, false);
    cubeVertex(1, 1, 0, BT, N, false);
    cubeVertex(1, 1, 1, BT, N, false);
    EndPrimitive();
    // top
    N = normalMatrix*vec3(0, 1, 0);
    cubeVertex(0, 1, 0, BT, N, true);
    cubeVertex(1, 1, 0, BT, N, true);
    cubeVertex(0, 1, 1, BT, N, true);
    cubeVertex(1, 1, 1, BT, N, true);
    EndPrimitive();
    // bottom
    N = normalMatrix*vec3(0, -1, 0);
    cubeVertex(0, 0, 0, BT, N, false);
    cubeVertex(1, 0, 0, BT, N, false);
    cubeVertex(0, 0, 1, BT, N, false);
    cubeVertex(1, 0, 1, BT, N, false);
    EndPrimitive();
}

void main( void )
{
    vec3 BT = (gl_in[0].gl_Position.xyz + 
               gl_in[1].gl_Position.xyz + 
               gl_in[2].gl_Position.xyz)/3;
    BT /= step;
    BT = step*vec3(round(BT));
	paintCube(BT);
}

