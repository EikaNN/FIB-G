#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
in float gtop;
in vec3 gnormal;
out vec4 fragColor;

uniform sampler2D lego;

const vec4 RED = vec4(1, 0, 0, 1);
const vec4 GREEN = vec4(0, 1, 0, 1);
const vec4 BLUE = vec4(0, 0, 1, 1);
const vec4 CYAN = vec4(0, 1, 1, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);

float min5(float x1, float x2, float x3, float x4, float x5) {
    float min1 = min(x1, x2);
    float min2 = min(x3, x4);
    return min(min(min1, min2), x5);
}

vec4 nearestColor(vec4 color) {
    float dR = distance(color, RED);
    float dG = distance(color, GREEN);
    float dB = distance(color, BLUE);
    float dC = distance(color, CYAN);
    float dY = distance(color, YELLOW);
    
    float dMin = min5(dR, dG, dB, dC, dY);

    if (dMin == dR) return RED;
    if (dMin == dG) return GREEN;
    if (dMin == dB) return BLUE;
    if (dMin == dC) return CYAN;
    return YELLOW;
}

void main()
{
    vec4 C = nearestColor(gfrontColor);
    vec4 TC = texture2D(lego, gtexCoord);
    if (gtop > 0) fragColor = C*TC*normalize(gnormal).z;
    else fragColor = C*normalize(gnormal).z;
}


