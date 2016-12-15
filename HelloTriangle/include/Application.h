#pragma once

#include <iostream>
#include "Object3D.h"

class Application {
public:
	Application();
	~Application();

	void loadShaders();
	void setup();
	void display();
	void reshape(int w, int h);


private:	
	std::string strVertexShader, strFragmentShader;

	Object3D triangle;
};

