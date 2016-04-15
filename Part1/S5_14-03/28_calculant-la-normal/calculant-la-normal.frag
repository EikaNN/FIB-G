#version 330 core

in vec4 frontColor;
in vec4 fragVertex;
out vec4 fragColor;

void main()
{
    vec4 dx = dFdx(fragVertex);
    vec4 dy = dFdy(fragVertex);

    //vec3 u = gl_FragCoord.x - x;
    //vec3 v = gl_FragCoord.y - y;

    vec3 N = normalize(cross(dx.xyz, dy.xyz));
    fragColor = frontColor * N.z;
}
