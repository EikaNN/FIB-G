#version 330 core

in vec3 Peye;
in vec3 Neye;
out vec4 fragColor;

uniform sampler2D glossy;
uniform int r = 1;

const float W = 512;
const float H = 512;
float DIV = (2*r+1)*(2*r+1);

vec4 sampleTexture(sampler2D sampler, vec2 st, int r)
{
    vec4 sum = vec4(0);
    for (int i = -r; i <= r; ++i) {
        for (int j = -r; j <= r; ++j) {
            sum += texture(sampler, st + vec2(i/W, j/H));
        }
    }     
   
	return sum/DIV;
}

vec4 sampleSphereMap(sampler2D sampler, vec3 R)
{
	float z = sqrt((R.z+1.0)/2.0);
	vec2 st = vec2((R.x/(2.0*z)+1.0)/2.0, (R.y/(2.0*z)+1.0)/2.0);
    st.y = -st.y;
	return sampleTexture(sampler, st, r);
}

void main()
{
	vec3 obs = vec3(0.0);
	vec3 I = normalize(Peye-obs);
	vec3 R = reflect(I, Neye);
	
	fragColor = sampleSphereMap(glossy, R);
}

