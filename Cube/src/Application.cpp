
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glm\matrix.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "ShaderFuncs.h"
#include "glm\vec3.hpp"

//	- 0.75f, 0.75f, 0.75f, 1.0f,	// 0
//	-0.75f, -0.75f, 0.75f, 1.0f,	// 1
//	0.75f, -0.75f, 0.75f, 1.0f,		// 2
//	0.75f, 0.75f, 0.75f, 1.0f,		// 3
//	0.75f, -0.75f, -0.75f, 1.0f,	// 4
//	0.75f, 0.75f, -0.75f, 1.0f,		// 5
//	-0.75f, -0.75f, -0.75f, 1.0f,	// 6
//	-0.75f, 0.75f, -0.75f, 1.0f,	// 7

char laberynt[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
};

GLfloat vertexPositions[] = {
	// Cara 1 (B1)
	-0.75f, 0.75f, 0.75f, 1.0f,		// 0
	-0.75f, -0.75f, 0.75f, 1.0f,	// 1
	0.75f, -0.75f, 0.75f, 1.0f,		// 2
	// Cara 1 (B2)
	-0.75f, 0.75f, 0.75f, 1.0f,		// 0
	0.75f, -0.75f, 0.75f, 1.0f,		// 2
	0.75f, 0.75f, 0.75f, 1.0f,		// 3
	// Cara 2 (C1)
	0.75f, 0.75f, 0.75f, 1.0f,		// 3
	0.75f, -0.75f, 0.75f, 1.0f,		// 2
	0.75f, -0.75f, -0.75f, 1.0f,	// 4
	// Cara 2 (C2)
	0.75f, 0.75f, 0.75f, 1.0f,		// 3
	0.75f, -0.75f, -0.75f, 1.0f,	// 4
	0.75f, 0.75f, -0.75f, 1.0f,		// 5
	// Cara 3 (D1)
	0.75f, 0.75f, -0.75f, 1.0f,		// 5
	0.75f, -0.75f, -0.75f, 1.0f,	// 4
	-0.75f, -0.75f, -0.75f, 1.0f,	// 6
	// Cara 3 (D2)
	0.75f, 0.75f, -0.75f, 1.0f,		// 5
	-0.75f, -0.75f, -0.75f, 1.0f,	// 6 
	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
	// Cara 4 (A1)
	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
	-0.75f, -0.75f, -0.75f, 1.0f,	// 6 
	-0.75f, -0.75f, 0.75f, 1.0f,	// 1
	// Cara 4 (A2)
	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
	-0.75f, -0.75f, 0.75f, 1.0f,	// 1 
	-0.75f, 0.75f, 0.75f, 1.0f,		// 0
	// Cara 5 (E1)
	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
	-0.75f, 0.75f, 0.75f, 1.0f,		// 0
	0.75f, 0.75f, 0.75f, 1.0f,		// 3
	// Cara 5 (E2)
	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
	0.75f, 0.75f, 0.75f, 1.0f,		// 3
	0.75f, 0.75f, -0.75f, 1.0f,		// 5
	// Cara 6 (F1)
	-0.75f, -0.75f, 0.75f, 1.0f,	// 1 
	-0.75f, -0.75f, -0.75f, 1.0f,	// 6
	0.75f, -0.75f, -0.75f, 1.0f,	// 4
	// Cara 6 (F2)
	-0.75f, -0.75f, 0.75f, 1.0f,	// 1 
	0.75f, -0.75f, -0.75f, 1.0f,	// 4
	0.75f, -0.75f, 0.75f, 1.0f,		// 2
};


GLfloat vertexColors[] = {
	//Cara 1 VERDE
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,

	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	//Cara 2 ROJO
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	//Cara 3 AZÚL
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,

	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	//Cara 4 NARANJA
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,

	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	//Cara 5 BLANCO
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,

	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	//Cara 6 AMARILLO
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,

	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
};

Application::Application() 
{}

Application::~Application() 
{}

void Application::setup()
{
	eye = glm::vec3(7.0f, 7.0f, 7.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	triangle.fAngleX = 0.0;
	triangle.fAngleY = 0.0;
	triangle.fAngleZ = 0.0;

	loadShaders();

	InitializeProgram(triangle.shader, strVertexShader, strFragmentShader);
	triangle.uniform = glGetUniformLocation(triangle.shader, "transform");

	triangle.numVertex = 36;
	glGenVertexArrays(1, &triangle.vao);
	glBindVertexArray(triangle.vao);
	glGenBuffers(1, &triangle.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0/*offset*/, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Application::update() {
	triangle.fAngleX = triangle.fAngleX + 0.001f;
	triangle.fAngleY = triangle.fAngleY + 0.001f;
	triangle.fAngleZ = triangle.fAngleZ + 0.001f;
}


void Application::display() {
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	miniMap();
}

void Application::loadShaders() {
	strVertexShader = loadTextFile("Shaders/passThru.vs");
	strFragmentShader = loadTextFile("Shaders/passThru.fs");
}

void Application::miniMap() {
	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
	//Seleccionamos los shaders a usar
	glUseProgram(triangle.shader);

	//activamos el vertex array object y dibujamos
	glBindVertexArray(triangle.vao);
	
	rotationX = glm::rotate(glm::mat4(1.0f), (triangle.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), (triangle.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), (triangle.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = rotationX * rotationY * rotationZ;
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 20.0f);
	rotation = pers * cam * rotation;

	// Pasamos valiables a variables uniform
	glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
	1, // El arreglo de matrices solo tiene una matriz
	false, // No queremos que saque la transpuesta
	glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz

	glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}



//	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
//	//Seleccionamos los shaders a usar
//	glUseProgram(triangle.shader);
//
//	//activamos el vertex array object y dibujamos
//	glBindVertexArray(triangle.vao);
//
//	//for (int j = 0; j < 5; j++) {
//	//	for (int i = 0; i < 5; i++) {
//	//		if (!laberynt[j][i]) {
//	//			continue;
//
//				rotationX = glm::rotate(glm::mat4(1.0f), (triangle.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//				rotationY = glm::rotate(glm::mat4(1.0f), (triangle.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//				rotationZ = glm::rotate(glm::mat4(1.0f), (triangle.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//				rotation = rotationX * rotationY * rotationZ;
//				cam = glm::lookAt(eye, target, up);
//				pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 20.0f);
//				rotation = pers * cam * rotation;
//
//				// Pasamos valiables a variables uniform
//				glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
//					1, // El arreglo de matrices solo tiene una matriz
//					false, // No queremos que saque la transpuesta
//					glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz
//
//				glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
//
//	//		}
//	//	}
//	//}