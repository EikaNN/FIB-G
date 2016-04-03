#version 330 core

in vec3 N;
in vec3 P;

out vec4 fragColor;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform mat4 modelViewMatrixInverse;

uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space

uniform bool world;

vec4 Phong(vec3 N, vec3 L, vec3 V)
{
    N = normalize(N);
    L = normalize(L);
    V = normalize(V);
    vec3 R = 2*dot(N, L)*N - L;    
    R = normalize(R);

    vec4 ambient = matAmbient*lightAmbient;
    vec4 diffuse = matDiffuse*lightDiffuse*max(0.0, dot(N, L));
    vec4 specular = matSpecular*lightSpecular*pow(max(0.0, dot(R, V)), matShininess);
    
    return ambient + diffuse + specular;
}

void main()
{
    if (world) {
        vec3 L = (modelViewMatrixInverse*lightPosition).xyz - P;
        // Posició de la càmera en OBJECT SPACE:
        //      modelViewMatrixInverse*vec4(0,0,0,1) = modelViewMatrixInverse[3]
        vec3 V = (modelViewMatrixInverse[3]).xyz - P;
        fragColor = Phong(N, L, V);
    }
    else {
        vec3 L = lightPosition.xyz - P;
        vec3 V = -P;
        fragColor = Phong(N, L, V);
    }
}   


