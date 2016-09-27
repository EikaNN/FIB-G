#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormalObj[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

const float speed = 1.2;
const float angSpeed = 8.0;


void main( void )
{
    vec3 averageN = (vnormalObj[0] + vnormalObj[1] + vnormalObj[2])/3;
    vec3 averageB = (gl_in[0].gl_Position.xyz +
                     gl_in[1].gl_Position.xyz +
                     gl_in[2].gl_Position.xyz)/3;

    float theta = angSpeed*time;
    mat3 Rz = mat3 (vec3(cos(theta), sin(theta), 0),
                    vec3(-sin(theta), cos(theta), 0),
                    vec3(0, 0, 1));
 
	for(int i = 0 ; i < 3 ; ++i)
	{
		gfrontColor = vfrontColor[i];
        vec3 V = gl_in[i].gl_Position.xyz - averageB;
        V = Rz*V;
        V = V + speed*time*averageN;
		gl_Position = modelViewProjectionMatrix*vec4(V, 1);
		EmitVertex();
	}
    EndPrimitive();
}
