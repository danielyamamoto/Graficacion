#include "Application.h"
#include <iostream>
#include <vector>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GLFW\glfw3.h"
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
	0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,	0.0, 1.0, 0.0, 1.0,
	//Cara 2 ROJO
	1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
	//Cara 3 AZÚL
	0.0, 0.0, 1.0, 1.0,	0.0, 0.0, 1.0, 1.0,	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,	0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0,
	//Cara 4 NARANJA
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 5 BLANCO
	1.0, 1.0, 1.0, 1.0,	1.0, 1.0, 1.0, 1.0,	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,	1.0, 1.0, 1.0, 1.0,	1.0, 1.0, 1.0, 1.0,
	//Cara 6 AMARILLO
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
};

GLfloat vertexPacman[] = {
	//Cara 1
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	//Cara 2
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	//Cara 3
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	//Cara 4
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	//Cara 5
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	//Cara 6
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,	1.0, 1.0, 0.0, 1.0,
};

GLfloat vertexPellets[] = {
	//Cara 1
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 2
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 3
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 4
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 5
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	//Cara 6
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0, 1.0, 0.3, 0.0, 1.0,
};

Application::Application() { }

Application::~Application() { }

void Application::loadShaders() {
	strVertexShader = loadTextFile("Shaders/passThru.vs");
	strFragmentShader = loadTextFile("Shaders/passThru.fs");
}

/*
//void Application::editorMap() {
//	/*glfwGetCursorPos(window, &mouseX, &mouseY);
//
//	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 0) {
//		for (int i = 0; i < 20; i++) {
//			for (int j = 0; j < 20; j++) {
//				if (!isFP) {
//					if (laberynt[j][i] == 0) {
//						laberynt[j][i] = 5;
//						puts("Caguama");
//					}
//					else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
//						if (laberynt[j][i] == 1) {
//							laberynt[j][i] = 5;
//							puts("Caguama");
//						}
//					}
//					else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
//						if (laberynt[j][i] == 5) {
//							laberynt[j][i] = 1;
//							puts("Caguama");
//						}
//					}
//				}
//			}
//		}
//	}*/
//}
//
//void Application::appGlfwGetCursorPos(double xpos, double ypos) {
//	puts("hola");
//}
//
//void Application::appGlfwGetMouseButton(int button) {
//	/*if (button == GLFW_MOUSE_BUTTON_LEFT) {
//		for (int i = 0; i < 20; i++) {
//			for (int j = 0; j < 20; j++) {
//				if (!isFP) {
//					if (laberynt[j][i] == 0) {
//						laberynt[j][i] = 5;
//						puts("Caguama");
//					}
//					else if (laberynt[j][i] == 1) {
//						laberynt[j][i] = 5;
//						puts("Caguama");
//					}
//				}
//			}
//		}
//	}
//	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
//		for (int i = 0; i < 20; i++) {
//			for (int j = 0; j < 20; j++) {
//				if (!isFP) {
//					if (laberynt[j][i] == 5) {
//						laberynt[j][i] = 1;
//						puts("Caguama");
//					}
//				}
//			}
//		}
//	}*/
//}

void Application::mouseCursor(double x, double y) {
	mouseX = x;
	mouseY = y;
}

void Application::mouseButton(int button) {
	if(GLFW_PRESS == GLFW_MOUSE_BUTTON_LEFT) {
		puts("hola");
	}
}

void Application::colisions() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (isFP) {
				float posEyeSavedX = fpEye.x; float posEyeSavedZ = fpEye.z;
				float posTarSavedX = fpTarget.x; float posTarSavedZ = fpTarget.z;
				float distWithCubes = glm::sqrt(((fpEye.x - (j * 1.5f)) * (fpEye.x - (j * 1.5f))) + ((fpEye.z - (i * 1.5f)) * (fpEye.z - (i * 1.5f))));
				if (distWithCubes < 0.5f) {
					if (laberynt[j][i] == 0) { laberynt[j][i] = 5; }
					else if (laberynt[j][i] == 1) {
						fpEye.x = posEyeSavedX; fpEye.z = posEyeSavedZ;
						fpTarget.x = posTarSavedX; fpTarget.z = posTarSavedZ;
					}
					else if (laberynt[j][i] == 2) { laberynt[j][i] == 5; }
					else if (laberynt[j][i] == 4) { laberynt[j][i] == 5; }
				}
			}
		}
	}
}

void Application::setup() {
	angle = (3.141592f / 180.0f);
	// Editor
	eEye = glm::vec3(15.0f, 1.0f, 15.0f);
	eTarget = glm::vec3(15.1f, 0.1f, 15.1f);
	eUp = glm::vec3(0.0f, 1.0f, 0.0f);
	// FirstPerson
	fpEye = glm::vec3(20.0f, 0.25f, 20.0f);
	fpTarget = glm::vec3(20.0f, 0.25f, 21.0f);
	fpUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fpTrasX = 1.5f;
	fpTrasY = 0.0f;
	fpTrasZ = 1.5f;

	loadShaders();

	InitializeProgram(walls.shader, strVertexShader, strFragmentShader);
	walls.uniform = glGetUniformLocation(walls.shader, "transform");
	walls.colorWalls = glGetUniformLocation(walls.shader, "drawColor");
	InitializeProgram(pellets.shader, strVertexShader, strFragmentShader);
	pellets.uniform = glGetUniformLocation(pellets.shader, "transform");

	walls.numVertex = 36;
	glGenVertexArrays(1, &walls.vao);
	glBindVertexArray(walls.vao);
	glGenBuffers(1, &walls.vbo);

	glBindBuffer(GL_ARRAY_BUFFER, walls.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Application::update() {
	colisions(); // Colisiones
	pellets.fAngleX = pellets.fAngleX + 1.0f;
	pellets.fAngleY = pellets.fAngleY + 1.0f;
	pellets.fAngleZ = pellets.fAngleZ + 1.0f;
}

void Application::display() {
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  

	glUseProgram(walls.shader);
	glBindVertexArray(walls.vao);

	if (isFP) { // FirstPerson
		fpCam = glm::lookAt(fpEye, fpTarget, fpUp);
		myPersTemp = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 40.0f);
		cam = myPersTemp * fpCam;
	}  
	else if (!isFP) { // Ortogonal
		eRotationX = glm::rotate(glm::mat4(1.0f), (-3.14f / 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 orto = glm::ortho(-0.75f, 29.0f, -0.75f, 29.0f);
		cam = orto * eRotationX;
	}
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			if (laberynt[j][i] == 0) { // Pellets
				scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 0.3));
				tras = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f * j, 0.0f, 1.5f * i));
				//rot = glm::rotate(glm::mat4(1.0f), (pellets.fAngleX * angle), glm::vec3(1.0f, 0.0f, 0.0f));
				myTrans = cam * tras * rot * scale;

				glUniform4fv(walls.colorWalls, 1, glm::value_ptr(glm::vec4(1.0, 0.8, 0.0, 1.0)));
				glUniformMatrix4fv(walls.uniform, 1, false, glm::value_ptr(myTrans));
				glDrawArrays(GL_TRIANGLES, 0, walls.numVertex);
			}
			else if (laberynt[j][i] == 1) { // Walls
				tras = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f * j, 0.0f, 1.5f * i));
				myTrans = cam * tras;

				glUniform4fv(walls.colorWalls, 1, glm::value_ptr(glm::vec4(0.3, 0.3, 0.3, 1.0)));
				glUniformMatrix4fv(walls.uniform, 1, false, glm::value_ptr(myTrans));
				glDrawArrays(GL_TRIANGLES, 0, walls.numVertex);
			}
			else if (laberynt[j][i] == 2) { // Ghosts
				scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
				tras = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f * j, 0.0f, 1.5f * i));
				myTrans = cam * tras * scale;

				glUniform4fv(walls.colorWalls, 1, glm::value_ptr(glm::vec4(1.0, 0.0, 0.0, 1.0)));
				glUniformMatrix4fv(walls.uniform, 1, false, glm::value_ptr(myTrans));
				glDrawArrays(GL_TRIANGLES, 0, walls.numVertex);
			}
			else if (laberynt[j][i] == 3) { // PacMan
				scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
				tras = glm::translate(glm::mat4(1.0f), glm::vec3(fpTrasX * j, fpTrasY, fpTrasZ * i));
				myTrans = cam * tras * scale;

				glUniform4fv(walls.colorWalls, 1, glm::value_ptr(glm::vec4(1.0, 1.0, 0.0, 1.0)));
				glUniformMatrix4fv(walls.uniform, 1, false, glm::value_ptr(myTrans));
				glDrawArrays(GL_TRIANGLES, 0, walls.numVertex);
			}
			else if (laberynt[j][i] == 4) { // PowerUps
				scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 0.3));
				tras = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f * j, 0.0f, 1.5f * i));
				myTrans = cam * tras * scale;

				glUniform4fv(walls.colorWalls, 1, glm::value_ptr(glm::vec4(0.0, 0.0, 1.0, 1.0)));
				glUniformMatrix4fv(walls.uniform, 1, false, glm::value_ptr(myTrans));
				glDrawArrays(GL_TRIANGLES, 0, walls.numVertex);
			}
			else if (laberynt[j][i] == 5) { // Nothing
			}
		}
	}
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}