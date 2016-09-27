#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 projectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 V = gl_in[i].gl_Position;
        gl_Position = projectionMatrix*V;
		EmitVertex();
	}
    EndPrimitive();
}
