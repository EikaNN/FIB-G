#version 330 core

in vec3 Neye;
in vec3 Peye;
out vec4 fragColor;

uniform mat3 normalMatrix;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space

uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess


vec4 Blinn_Phong(vec3 N, vec3 L, vec3 V)
{
    N = normalize(N);
    L = normalize(L);
    V = normalize(V);
    vec3 H = normalize(V+L); 
    vec4 ambient = matAmbient*lightAmbient;
    vec4 diffuse = matDiffuse*lightDiffuse*max(0.0, dot(N, L));
    vec4 specular = matSpecular*lightSpecular*pow(max(0.0, dot(N, H)), matShininess);
    return ambient + diffuse + specular;
}

void main()
{
    vec3 L = lightPosition.xyz - Peye;
    vec3 V = vec3(0.0, 0.0, 1.0);
    
    fragColor = Blinn_Phong(Neye, L, V);
}

