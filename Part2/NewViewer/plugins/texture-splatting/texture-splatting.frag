#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;

void main() 
{
	float r = texture(sampler0, vtexCoord).r;
	fragColor = mix(texture(sampler1, vtexCoord), texture(sampler2, vtexCoord), fract(r));
}