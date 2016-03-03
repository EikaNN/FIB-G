
#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;

uniform float time;

void main() {
    float slice = 1.0/30.0;
    int frame = int(mod(time/slice, 48));
}
