#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform bool classic = false;

const float PI = 3.141592;

void main()
{
    vec2 centre = vec2(0.5, 0.5);
    float d = distance(vtexCoord, centre);
    float cercle = step(0.2, d);

    if (!classic && cercle > 0.0) {
        vec2 u = vtexCoord - centre;
        float phi = PI/16;
        float theta = atan(u.t, u.s);
        float raig = 1-step(mod(theta/phi + 0.5, 2), 1);
        fragColor = vec4(1, raig, raig, 1);
    }
    else fragColor = vec4(1, cercle, cercle, 1);
}

