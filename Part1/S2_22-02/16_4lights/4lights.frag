#version 330 core

uniform float time;
uniform bool rotate=true;

in vec3 Nobj;
in vec3 Pobj;
out vec4 fragColor;

uniform mat4 modelViewMatrixInverse;


// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V és el vector unitari cap a l'observador
// N és la normal
// P és la posició 
// lightPos és la posició de la llum
// lightColor és el color de la llum
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor)
{
	const float shininess = 100.0;
	const float Kd = 0.5;
	N = normalize(N);
	vec3 L = normalize(lightPos - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float spec =  pow( RdotV, shininess);
	return vec4(Kd*lightColor*NdotL + vec3(spec),0);
}

void main()
{
    // Lights
    vec3 posFocusGreen = vec3(0, 10, 0);
    vec3 colFocusGreen = vec3(0, 1, 0);    
    vec3 posFocusYellow = vec3(0, -10, 0);
    vec3 colFocusYellow = vec3(1, 1, 0);    
    vec3 posFocusBlue = vec3(10, 0, 0);
    vec3 colFocusBlue = vec3(0, 0, 1);
    vec3 posFocusRed = vec3(-10, 0, 0);
    vec3 colFocusRed = vec3(1, 0, 0);

    // Posicio observador en coordenades Eye Space: (0, 0, 0, 1)
	vec3 Vobj = (modelViewMatrixInverse*vec4(0,0,0,1)).xyz - Pobj;
    Vobj = normalize(Vobj);

    mat3 R = mat3 (
        cos(time),   sin(time), 0.0,
        -sin(time),  cos(time), 0.0,
        0.0,         0.0,       1.0
    );

    if (rotate) {
        posFocusGreen = R*posFocusGreen;
        posFocusYellow = R*posFocusYellow;
        posFocusBlue = R*posFocusBlue;
        posFocusRed = R*posFocusRed;
    }

    posFocusGreen = (modelViewMatrixInverse*vec4(posFocusGreen, 1.0)).xyz;
    posFocusYellow = (modelViewMatrixInverse*vec4(posFocusYellow, 1.0)).xyz;
    posFocusBlue = (modelViewMatrixInverse*vec4(posFocusBlue, 1.0)).xyz;
    posFocusRed = (modelViewMatrixInverse*vec4(posFocusRed, 1.0)).xyz;    

    vec4 lightGreen = light(Vobj, Nobj, Pobj, posFocusGreen, colFocusGreen);
    vec4 lightYellow = light(Vobj, Nobj, Pobj, posFocusYellow, colFocusYellow);
    vec4 lightBlue = light(Vobj, Nobj, Pobj, posFocusBlue, colFocusBlue);
    vec4 lightRed = light(Vobj, Nobj, Pobj, posFocusRed, colFocusRed);
    //vec4 lightBlanc = light(Vobj, N, P, vec3(0, 0, 0), vec3(1, 1, 1));
	fragColor = lightGreen + lightYellow + lightBlue + lightRed;
}


