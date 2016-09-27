#version 330 core

layout(triangles) in; 
layout(triangle_strip, max_vertices = 36) out;

in vec4 vcolor[];
//in vec3 vnormal[];
out vec4 gcolor; 

uniform float time;

void main( void )
{
    int grup = (17 * gl_PrimitiveIDIn + 19) % 10;

    float move = pow(clamp((time - grup)/4), 2);

    for( int i = 0 ; i < 3 ; i++ ) 
     { 
        gcolor = vcolor[i]; 
        gl_Position = gl_in[i].gl_Position; 
        EmitVertex(); 
     } 
     EndPrimitive(); 
};
