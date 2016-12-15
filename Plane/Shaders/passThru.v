#version 430 core

layout (location = 0) in vec4 vPosition;

uniform mat4 mTransform;
uniform float fTime;
uniform vec3 vEye;
uniform vec3 myLightPosition;

out vec4 color;

float F(float x, float z) {
	return 4.0 * cos  (0.02 * (x*x + z*z) + fTime); 
}


void main()
{
	//vec4 v = vPosition;
	//v = (1.0, sin(5x)*cos(5y)/5, 1.0, 1.0);
	
	//vec4 vNewVec = vPosition;
	//calculamos la altura de este vertice
	//vNewVec.y = F(vNewVec.x, vNewVec.z);

	color = vec4(1.0, 1.0, 1.0, 1.0); // NO BORRAR
	gl_Position = mTransform * vPosition;
}
