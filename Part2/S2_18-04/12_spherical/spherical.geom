#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec2 gtexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform float side = 0.1;

void quadVertex(int i, int j, int oi, int oj, vec3 V) {
    gtexCoord = vec2(i, j);
    float offset = side/2;
    vec3 aux = vec3(V.x+oi*offset, V.y+oj*offset, V.z);
    //vec3 aux = vec3(V.x-offset, V.y-offset, V.z);
    gl_Position = projectionMatrix*vec4(aux, 1);
    EmitVertex();
}

void paintQuad(vec4 V) {
    quadVertex(0, 0, -1, -1, V.xyz);
    quadVertex(1, 0, 1, -1, V.xyz);
    quadVertex(0, 1, -1, 1, V.xyz);
    quadVertex(1, 1, 1, 1, V.xyz);
    EndPrimitive();
}

void main( void )
{
	paintQuad(modelViewMatrix*gl_in[0].gl_Position);
}

/*
#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform float side = 0.1;

void main( void )
{
    vec4 P_obs = modelViewMatrix * gl_in[0].gl_Position;
    vec4 P1 = P_obs + vec4(side,0,0,0);
    vec4 P2 = P_obs + vec4(0,side,0,0);
    vec4 P3 = P_obs + vec4(side,side,0,0);
    gtexCoord = vec2(0,0);
    gl_Position = projectionMatrix * P_obs;
    EmitVertex();
    gtexCoord = vec2(1,0);
    gl_Position = projectionMatrix * P1;
    EmitVertex();
    gtexCoord = vec2(0,1);
    gl_Position = projectionMatrix * P2;
    EmitVertex();
    gtexCoord = vec2(1,1);
    gl_Position = projectionMatrix * P3;
    EmitVertex();
    EndPrimitive();
}
*/
