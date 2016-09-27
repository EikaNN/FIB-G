#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
        vec4 Pclip = gl_in[i].gl_Position;  
        vec4 Pndc = Pclip / Pclip.w;        // obtenim coordenades en NDC
        Pndc = Pndc + vec4(0.5, 0, 0, 0);   // traslacio en X de 0.5
		gl_Position = Pndc;
		EmitVertex();
	}
    EndPrimitive();

    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
        vec4 Pclip = gl_in[i].gl_Position;
        vec4 Pndc = Pclip / Pclip.w;
        Pndc = Pndc + vec4(-0.5, 0, 0, 0);  // traslacio en X de 0.5
		gl_Position = Pndc;
		EmitVertex();
	}
    EndPrimitive();

    
}
