#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.2;

const vec4 GREY = vec4(vec3(0.8), 1);

void cubeVertex(float x, float y, float z, vec3 BT, vec3 N) 
{
    gfrontColor = GREY*N.z;
    vec3 V = vec3(x-0.5, y-0.5, z-0.5)*step;
    //vec3 V = vec3(x, y, z)*step;
    gl_Position = modelViewProjectionMatrix*vec4(V + BT, 1);
    EmitVertex();
}

void paintCube(vec3 BT) 
{
    // front
    vec3 N = normalMatrix*vec3(0, 0, -1);
    cubeVertex(0, 0, 0, BT, N);
    cubeVertex(1, 0, 0, BT, N);
    cubeVertex(0, 1, 0, BT, N);
    cubeVertex(1, 1, 0, BT, N);
    EndPrimitive();
    // back
    N = normalMatrix*vec3(0, 0, 1);
    cubeVertex(0, 0, 1, BT, N);
    cubeVertex(1, 0, 1, BT, N);
    cubeVertex(0, 1, 1, BT, N);
    cubeVertex(1, 1, 1, BT, N);
    EndPrimitive();
    // left
    N = normalMatrix*vec3(-1, 0, 0);
    cubeVertex(0, 0, 0, BT, N);
    cubeVertex(0, 0, 1, BT, N);
    cubeVertex(0, 1, 0, BT, N);
    cubeVertex(0, 1, 1, BT, N);
    EndPrimitive();
    // right
    N = normalMatrix*vec3(1, 0, 0);
    cubeVertex(1, 0, 0, BT, N);
    cubeVertex(1, 0, 1, BT, N);
    cubeVertex(1, 1, 0, BT, N);
    cubeVertex(1, 1, 1, BT, N);
    EndPrimitive();
    // top
    N = normalMatrix*vec3(0, 1, 0);
    cubeVertex(0, 1, 0, BT, N);
    cubeVertex(1, 1, 0, BT, N);
    cubeVertex(0, 1, 1, BT, N);
    cubeVertex(1, 1, 1, BT, N);
    EndPrimitive();
    // bottom
    N = normalMatrix*vec3(0, -1, 0);
    cubeVertex(0, 0, 0, BT, N);
    cubeVertex(1, 0, 0, BT, N);
    cubeVertex(0, 0, 1, BT, N);
    cubeVertex(1, 0, 1, BT, N);
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
