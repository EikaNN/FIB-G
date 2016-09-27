#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

const vec4 BLACK = vec4(0, 0, 0, 1);

bool is_valid(float x)
{
    return x >= 0 && x <= 1;
}

void main()
{
    float u = vtexCoord.x*2 - 1;
    float v = vtexCoord.y*2 - 1;
    vec2 Q = vec2(u, v);
    float r = length(Q);
    float rp = (r + 0.22*pow(r, 3) + 0.24*pow(r,5));
    vec2 Qp = rp*normalize(Q);
    float s = (Qp.x+1)/2;
    float t = (Qp.y+1)/2;
    if (is_valid(s) && is_valid(t)) fragColor = texture(colorMap, vec2(s,t));
    else fragColor = BLACK;
}
