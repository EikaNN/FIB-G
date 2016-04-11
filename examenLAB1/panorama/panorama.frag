#version 330 core

in vec3 Pobj;
out vec4 fragColor;

uniform sampler2D panorama;

const float PI = 3.141592;

void main()
{
    float psi = asin(Pobj.y);
    float theta = atan(Pobj.z, Pobj.x);
    float s = theta / (2*PI);
    float t = (psi/PI) + 0.5;
    fragColor = texture(panorama, vec2(s, t));
}
