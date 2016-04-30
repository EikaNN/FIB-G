#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormalObj[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const float speed = 0.5;

void main( void )
{
    vec3 average = (vnormalObj[0] + vnormalObj[1] + vnormalObj[2])/3;
	for(int i = 0 ; i < 3 ; ++i)
	{
		gfrontColor = vfrontColor[i];
        vec4 V = gl_in[i].gl_Position + speed*time*vec4(average, 0);
		gl_Position = modelViewProjectionMatrix*V;
		EmitVertex();
	}
    EndPrimitive();
}
