#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMax; 
uniform vec3 boundingBoxMin;

const vec4 BLACK = vec4(0, 0, 0, 1);
const vec4 CYAN = vec4(0, 1, 1, 1);

void drawFloor()
{
    float R = distance(boundingBoxMin, boundingBoxMax)/2.0;
    vec3 C = (boundingBoxMin + boundingBoxMax)/2.0;
    C.y = boundingBoxMin.y-0.01;
    gfrontColor = CYAN;
    
    vec4 Pobj0 = vec4(C.x-R, C.y, C.z-R, 1);
    gl_Position = modelViewProjectionMatrix*Pobj0;
    EmitVertex();
    
    vec4 Pobj1 = vec4(C.x+R, C.y, C.z-R, 1);
    gl_Position = modelViewProjectionMatrix*Pobj1;
    EmitVertex();

    vec4 Pobj2 = vec4(C.x-R, C.y, C.z+R, 1);
    gl_Position = modelViewProjectionMatrix*Pobj2;
    EmitVertex();

    vec4 Pobj3 = vec4(C.x+R, C.y, C.z+R, 1);
    gl_Position = modelViewProjectionMatrix*Pobj3;
    EmitVertex();
    
    EndPrimitive();  
}

void main( void ) 
{    
    if (gl_PrimitiveIDIn == 0) drawFloor();

    for(int i = 0 ; i < 3 ; i++) 
    {
        gfrontColor = vfrontColor[i];
        gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

    for(int i = 0 ; i < 3 ; i++) 
    {
        gfrontColor = BLACK;
        vec4 Pobj = gl_in[i].gl_Position;
        Pobj.y = boundingBoxMin.y;
        gl_Position = modelViewProjectionMatrix*Pobj;
        EmitVertex();
    }
    EndPrimitive();
}

