#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

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
    vec3 Neye = normalMatrix * normal;
    vec4 Peye = modelViewMatrix * vec4(vertex, 1.0);

    // V és el vector del vèrtex cap a la càmera
    //      càmera(0, 0, 0) - Peye = -Peye
    vec3 Veye = -Peye.xyz;

    // Leye és el vector del vèrtex cap a la font de llum
    vec3 Leye = lightPosition.xyz - Peye.xyz;

    frontColor = Phong(Neye, Leye, Veye);

    gl_Position = projectionMatrix * Peye;
}

