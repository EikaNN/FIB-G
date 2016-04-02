#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D map;
uniform float time;
uniform float a = 0.5;

const float PI = 3.141592;

void main()
{
    vec3 color = texture(map, vtexCoord).xyz;
    float m = max(color.x, max(color.y, color.z));
    vec2 u = vec2(m, m);
    float phi = 2*PI*time;
    mat2 R = mat2(
                    vec2(cos(phi), sin(phi)),
                    vec2(-sin(phi), cos(phi))
                 );
    u = R*u;
    vec2 offset = (a/100.0)*u;
    fragColor = texture(map, vtexCoord+offset);
}
