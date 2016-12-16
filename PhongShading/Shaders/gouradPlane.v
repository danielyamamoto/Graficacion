#version 430 core

layout (location = 0) in vec4 vPosition;

uniform mat4 mTransform;
uniform float fTime;
uniform vec3 myLightPosition;

out vec3 newNormal;
out vec3 lightv;
out vec4 vNewVec;

float Dp(float a, float b) {
	return -4.0 * a * 0.04 * 1 / (0.5 * (a * a + b * b ) + fTime);
}

float F(float x, float z) {
	return 100 * ((x*x+z*z)*0.01-fTime) / sqrt(10 * ((1*(x*x+z*z)/1) + (2*(x*x+z*z)/2) + (3*(x*x+z*z)/3)));			// CascadaDown
	
	//return 4 * cos((x*x+z*z)*0.01-fTime) + (cos(1*(x*x+z*z))/1 + (cos(2*(x*x+z*z))/2) + cos(3*(x*x+z*z))/3);			// Onda

	//return 1.005 * ((x*x+z*z)*0.01-fTime) / 15 * ((1*(x*x+z*z)/1) + (2*(x*x+z*z)/2) + (3*(x*x+z*z)/3));				// CascadaUp

	//return 4 * sin((x*x+z*z)*0.01-fTime) +  sqrt((sin(1*(x*x+z*z))/1 + (sin(2*(x*x+z*z))/2) + sin(3*(x*x+z*z))/3));	// ConoTriangle
}

vec3 calculateNormal (vec4 v) {
	vec3 vt1 = vec3(1.0, Dp(v.x, v.z), 0.0);
	vec3 vt2 = vec3(0.0, Dp(v.z, v.x), 1.0);

	return cross (vt1, vt2);
}

void main() {
	 vNewVec = vPosition;
	//calculamos la altura de este vertice
	vNewVec.y = F(vNewVec.x, vNewVec.z);

	//CALCULO DE NORMALES
	vec3 normal = normalize(calculateNormal (vNewVec));
	mat4 matForNormals = transpose(inverse(mTransform));
    newNormal = normalize(matForNormals * vec4(normal, 1.0)).xyz;

	//calculo de posicion de luz
	lightv = normalize( myLightPosition - vNewVec.xyz);

	 gl_Position = mTransform * vNewVec;
}