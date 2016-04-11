#version 330 core

in vec4 frontColor;
in vec3 Peye;
in vec3 Neye;
out vec4 fragColor;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space

uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform float f = 4.0;

vec4 Phong(vec3 N, vec3 L, vec3 V)
{
    N = normalize(N);
    L = normalize(L);
    V = normalize(V);
    vec3 R = 2*dot(N, L)*N - L;    
    R = normalize(R);

    vec4 ambient = matAmbient*lightAmbient;
    vec4 diffuse = matDiffuse*lightDiffuse*max(0.0, dot(N, L));
    vec4 specular = matSpecular*lightSpecular*cos(f*(acos(dot(R, V))));
    return ambient + diffuse + specular;
}


void main()
{
    vec3 L = lightPosition.xyz - Peye;
    vec3 V = -Peye;
    
    fragColor = Phong(Neye, L, V);
}
