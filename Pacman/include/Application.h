#pragma once
#include <iostream>
#include "Object3D.h"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "GLFW\glfw3.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

class Application {
public:
	Application();
	~Application();

	char laberynt[20][20] = {
	//1  2  3  4  0  6  7  8  9  10 11 12 13 14 10 16 17 18 19 20
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 1
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 }, // 2
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 }, // 3
	{ 1, 0, 1, 4, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 4, 1, 0, 1 }, // 4
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1 }, // 0
	{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // 6
	{ 1, 0, 1, 1, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1 }, // 7
	{ 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1 }, // 8
	{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 }, // 9
	{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1 }, // 10
	{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1 }, // 11
	{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 }, // 12
	{ 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1 }, // 13
	{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4, 1, 0, 1, 1, 0, 1 }, // 14
	{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // 10
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1 }, // 16
	{ 1, 0, 1, 4, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 4, 1, 0, 1 }, // 17
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 }, // 18
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 }, // 19
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // 20
	// 0 = Pellets
	// 1 = Walls
	// 2 = Ghosts
	// 3 = Pacman
	// 4 = PowerUps
	// 0 = Nothing
};
	bool isFP;
	bool isMoving = false;
	int idCube;
	float camRotX, camRotY, camRotZ;
	float camTrasX, camTrasY, camTrasZ;
	// Mouse & KeyBoard
	double mouseX, mouseY, velMouse;
	bool isMouseActive;

	void keyBoard(int key, int scancode, int action, int mods);
	void mouseCursor(double x, double y);
	void mouseButton(int button, int action, int mods);
	void colisions();

	void setup();
	void update();
	void display();
	void loadShaders();
	void reshape(int w, int h);
	
	// FirstPerson
	float fpTras;
	float fpTrasX;
	float fpTrasY;
	float fpTrasZ;

	glm::mat4 fpRotation;
	glm::mat4 fpRotationX;
	glm::mat4 fpRotationY;
	glm::mat4 fpRotationZ;

	glm::vec4 fpRot;
	glm::vec3 fpEye;
	glm::vec3 fpTarget;
	glm::vec3 fpUp;

private:	
	std::string strVertexShader, strFragmentShader;
	GLFWwindow* window;
	Object3D walls;
	Object3D pellets;
	float angle;
	glm::mat4 myTrans;
	glm::mat4 myPersTemp;

	// Camara & Perspective
	glm::mat4 cam;
	glm::mat4 pers;
	glm::mat4 eCam;
	glm::mat4 fpCam;
	glm::mat4 ePers;
	glm::mat4 pCam;
	
	// Laberynt
	glm::mat4 scale;
	glm::mat4 scaleX;
	glm::mat4 scaleY;
	glm::mat4 scaleZ;

	glm::mat4 tras;
	glm::mat4 trasX;
	glm::mat4 trasY;
	glm::mat4 trasZ;

	glm::mat4 rot;
	glm::mat4 rotX;
	glm::mat4 rotY;
	glm::mat4 rotZ;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	// Editor
	glm::mat4 eTras;
	glm::mat4 eTrasX;
	glm::mat4 eTrasY;
	glm::mat4 eTrasZ;

	glm::mat4 eRotation;
	glm::mat4 eRotationX;
	glm::mat4 eRotationY;
	glm::mat4 eRotationZ;

	glm::vec3 eEye;
	glm::vec3 eTarget;
	glm::vec3 eUp;
};