#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

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
    vec3 Neye = normalMatrix * normal;

    // V és el vector del vèrtex cap a la càmera, aquí valor per defecte de OpenGL
    vec3 V = vec3(0.0, 0.0, 1.0);

    // Peye és la posició del vèrtex
    vec3 Peye = (modelViewMatrix * vec4(vertex, 1.0)).xyz;

    // L és el vector del vèrtex cap a la font de llum
    vec3 Leye = lightPosition.xyz - Peye;

    frontColor = Blinn_Phong(Neye, Leye, V);

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}


