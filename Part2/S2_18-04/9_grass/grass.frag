#version 330 core

in vec3 gnormal;
in vec3 gPos;
out vec4 fragColor;

const vec4 GREY = vec4(vec3(0.8), 1);

uniform mat3 normalMatrix;
uniform float d = 0.1;

uniform sampler2D grass_top0;
uniform sampler2D grass_side1;

void main()
{
    bool vertical = gnormal.z == 0;
    if (vertical)
    {
        vec2 st = vec2(4*(gPos.x - gPos.y), gPos.z/d);
        fragColor = texture2D(grass_side1, st);
        if (fragColor.a < 0.1) discard;
    }
    else
    {
        vec2 st = 4*gPos.xy;
        fragColor = texture2D(grass_top0, st);
    }
}   

