#version 330 core

in vec3 Nobj;
in vec3 Pobj;
out vec4 fragColor;

uniform int M = 4;

const vec4 BLUE = vec4(0, 0, 1, 1);
const vec4 ORANGE = vec4(1, 0.5, 0, 1);
const vec4 RED = vec4(1, 0, 0, 1);
const vec4 GREEN = vec4(0, 1, 0, 1);
const vec4 YELLOW = vec4(1, 1, 0, 1);
const vec4 WHITE = vec4(1, 1, 1, 1);
const vec4 BLACK = vec4(0, 0, 0, 1);

uniform vec3 boundingBoxMin; 
uniform vec3 boundingBoxMax;

// Retorna quina és la component dominant de N i el seu signe
// Exemple: Si retorna 1, la component màxima és la x i és positiva
//          Si retorna -3, la component màxima és la z i és negativa
int dominant(vec3 N) {
    float x = abs(N.x);
    float y = abs(N.y);
    float z = abs(N.z);
    float max1 = max(x, y);
    int res;
    if (max1 == x) res = 1;
    else res = 2;
    float max2 = max(max1, z);
    if (max2 == z) res = 3;
    if (N[res-1] < 0) res *= -1;
    return res;
}
        
vec4 color(vec3 N) {
    int d = dominant(N);
    if (d == 1) return RED;
    if (d == -1) return GREEN; 
    if (d == 2) return BLUE;
    if (d == -2) return ORANGE;
    if (d == 3) return YELLOW;
    return WHITE;
}


bool isBlack(float x) {
    return fract(x) <= 0.05 || fract(x) >= 0.95;
}


void main()
{
    float xmin = boundingBoxMin.x;
    float ymin = boundingBoxMin.y;
    float zmin = boundingBoxMin.z;
    float xmax = boundingBoxMax.x;
    // Com és un un cub total serà el mateix per abs(ymax - ymin) i abs(zmax - zmin)
    float total = abs(xmax - xmin);
    float x = ((Pobj.x - xmin) / total)*M;
    float y = ((Pobj.y - ymin) / total)*M;
    float z = ((Pobj.z - zmin) / total)*M;

    if (isBlack(x) && isBlack(y)) fragColor = BLACK;
    else if (isBlack(x) && isBlack(z)) fragColor = BLACK;
    else if (isBlack(y) && isBlack(z)) fragColor = BLACK;
    else fragColor = color(Nobj);
}


