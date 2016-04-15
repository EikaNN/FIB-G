#version 330 core

in vec4 Pobj;
in vec3 Nobj;
out vec4 fragColor;

uniform sampler2D noise0;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

const vec4 S = 0.3*vec4(0, 1, -1, 0);
const vec4 T = 0.3*vec4(-2, -1, 1, 0);
const vec4 WHITE = vec4(1, 1, 1, 1);
const vec4 REDISH = vec4(0.5, 0.2, 0.2, 1);


vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
    vec3 lightPos = vec3(0.0,0.0,2.0);
    vec3 L = normalize(lightPos - Pos);
    vec3 V = normalize(-Pos);
    vec3 R = reflect(-L,N);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R,V));
    float Ispec = pow(RdotV, 20.0);
    return diffuse*NdotL + Ispec;
}

void main()
{
    float s = dot(S, Pobj);
    float t = dot(T, Pobj);

    float v = 2*texture(noise0, vec2(s,t)).x;
    vec4 diffuse = WHITE;
    if (v < 1) diffuse = mix(WHITE, REDISH, fract(v));
    else if (v < 2) diffuse = mix(REDISH, WHITE, fract(v));

    vec3 Neye = normalize(normalMatrix*Nobj);
    vec4 Peye = modelViewMatrix*Pobj;
    fragColor = shading(Neye, Peye.xyz, diffuse);
}

