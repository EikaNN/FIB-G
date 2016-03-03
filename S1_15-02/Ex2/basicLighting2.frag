#version 330 core

in vec3 fragNormal;
in vec3 outColor;
out vec4 fragColor;


void main()
{
    vec3 N = normalize(fragNormal);
    fragColor = vec4(outColor,1.0) * N.z;
}
