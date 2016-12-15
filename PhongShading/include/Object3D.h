#pragma once

#include <iostream>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class Object3D{
public:
	GLuint	vao, //Vertex Array Object
			vbo; //Vertex Buffer Object

	int numVertex; //numero de vertices para este objeto

	GLuint shader; //referencia a los shaders
	GLuint uniform; // Para almacenar el �ngulo
	float fAngle;
	float fAngleX, fAngleY, fAngleZ;
	float time;
	float eye;
	float myLight;
};

