#version 330 core

layout (location=0) in vec3 vertex;
layout (location=2) in vec3 color;

uniform mat4 modelViewProjectionMatrix;

out vec4 frontColor;

void main() {
	frontColor = vec4(color, 1);
  	gl_Position = modelViewProjectionMatrix*(vec4(vertex, 1));
}
