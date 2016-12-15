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
#include "SOIL.h"

Application::Application() : plane() { }

Application::~Application() { }

void Application::loadShaders() {
	sVertex = loadTextFile("Shaders/passThru.v");
	sFragment = loadTextFile("Shaders/passThru.f");
	
	vGourad = loadTextFile("Shaders/gouradPlane.v");
}

void Application::initTexture() {
	// Soil pone la imagen de cabeza 
	int imgWidth, imgHeight, rgb;
	unsigned char* img = SOIL_load_image("lenna.png", &imgWidth, &imgHeight, &rgb, 0);
	glGenTextures(1, &plane.texture_id);
	glBindTexture(GL_TEXTURE_2D, plane.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img); // Liberamos la memoria del SOIL

	// Generate trilinear 
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Trilinear filtering
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	// Bilinear filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	
	// Como manejamos la imagen (corte, repetir)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // X
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Y

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::setup() {
	eye = glm::vec3(0.0f, 50.0f, 105.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	vEye = glm::vec3(0.0f, 100.0f, 100.0f);

	plane.fAngleX = 0.0;
	plane.fAngleY = 0.0;
	plane.fAngleZ = 0.0;

	plane.createPlane(1);
	loadShaders();
	initTexture();

	InitializeProgram(plane.shader, sVertex, sFragment);
	
	plane.uTexture = glGetUniformLocation(plane.shader, "theTexture0");
	plane.uTransform[0] = glGetUniformLocation(plane.shader, "mTransform");
	plane.uTime[0] = glGetUniformLocation(plane.shader, "fTime");
	plane.uEye[0] = glGetUniformLocation(plane.shader, "vEye");
	uMyLightPosition[0] = glGetUniformLocation(plane.shader, "myLightPosition");

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);

	glBufferData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes() + plane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane.getVertexSizeInBytes(), plane.plane);
	glBufferSubData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes(), plane.getTextureCoordsSizeInBytes(), plane.textureCoords);
	plane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)plane.getVertexSizeInBytes());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST); // Field of view
}

void Application::update() {
	plane.fAngleY = plane.fAngleY + 0.1f; // PC
	//plane.fAngleY = plane.fAngleY + 0.05f; // LAP
}


void Application::display() {
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glUseProgram(plane.shader);
	glBindVertexArray(plane.vao);

	glm::mat4 myAllTransformations;
	rotationX = glm::rotate(glm::mat4(1.0f), (plane.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), (plane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), (plane.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = rotationX * rotationY * rotationZ;
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 180.0f);
	rotation = pers * cam * rotation;

	glUseProgram(plane.shader);
	glUniformMatrix4fv(plane.uTransform[0], 1, GL_FALSE, glm::value_ptr(rotation));
	glUniform1f(plane.uTime[0], plane.time);
	glUniform1f(plane.uEye[0], plane.eye);
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());

	// Texture 0 Lenna
	glBindTexture(GL_TEXTURE_2D, plane.texture_id);
	glUniform1i(plane.uTexture, 0);
	glActiveTexture(GL_TEXTURE0);

	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());
}

void Application::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}