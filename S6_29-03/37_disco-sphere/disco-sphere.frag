#version 330 core

in vec3 Veye;
out vec4 fragColor;

uniform sampler2D sampler;

void main()
{

    vec3 dx = dFdx(Veye);
    vec3 dy = dFdy(Veye);
    vec3 N = normalize(cross(dx.xyz, dy.xyz));
    fragColor = texture(sampler, vec2(N.x, N.y)) * N.z;
}
