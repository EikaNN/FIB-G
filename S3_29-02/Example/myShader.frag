#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colorMap;
uniform sampler2D colorMap2; // unit2
uniform float time;

const float PI = 3.14159;

void main()
{

    float t = abs(sin(2.0*PI*time*1.0));    
    fragColor = mix(texture(colorMap, vtexCoord), texture(colorMap2, vtexCoord), t);
}
