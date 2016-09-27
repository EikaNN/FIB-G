#version 330 core

uniform vec4 color;

in vec4 frontColor;
out vec4 fragColor;

const vec4 WHITE = vec4(1.0);

void main() 
{
	if (color == WHITE) fragColor = frontColor; //paint BoundingBox
	else fragColor = color;
}
