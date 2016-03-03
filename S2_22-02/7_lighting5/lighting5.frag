#version 330 core

in vec3 Nworld;
in vec3 Vworld;
in vec3 Lworld;

in vec3 Neye;
in vec3 Veye;
in vec3 Leye;

out vec4 fragColor;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular

uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

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
    if (world) fragColor = Phong(Nworld, Lworld, Vworld);
    else fragColor = Phong(Neye, Leye, Veye);
}   


