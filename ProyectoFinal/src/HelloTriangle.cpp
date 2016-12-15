#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;
int timer = 0; float angle = 0;
int screenX = 640; int screenY = 480;
int xpos, ypos;
float vel = 0.01f;

//Se tiene que llamar despues de inicializar la ventana y el OpenGL, pero antes del main loop
void setup() {
	app.setup();
}

//Se ejecuta siempre que se necesite actualizar la imagen
void display() {
	app.display();
}

//Se ejecuta cuando la ventana cambia de tamaño. Parámetros en pixeles.
//(ojo: En otros programas se debe ejecutar glViewport)
void reshape(int w, int h) {
	app.reshape(w, h);
}

int main(int argc, char *argv[]) {
	Application app;
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) { return -1; }

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenX, screenY, "Pacman", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Make the window's context current

	glewExperimental = GL_TRUE; 
	glewInit();
	app.setup();

	// get version info 
	const GLubyte* renderer = glGetString (GL_RENDERER); 
	const GLubyte* version = glGetString (GL_VERSION); 
	printf (" Renderer: %s\ n", renderer); 
	printf (" OpenGL version supported %s\ n", version); 

	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
	glEnable(GL_DEPTH_TEST); // Habilita el z-buffer

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents(); // Update other events like input handling
		app.update(); // Update de Application
		app.display(); // Put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		
		//glfwSetMouseButtonCallback(window, app.mouseButton);
		//GLFWkeyfun(window, int key, int scancode, int action, int mods);
		


		if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT)) {
			app.isFP = false;

		}

		glfwGetTime();
		timer++;
		if (timer >= 30) {
			if (glfwGetKey(window, GLFW_KEY_E)) { app.isFP = false; }	  // Editor
			else if (glfwGetKey(window, GLFW_KEY_R)) { app.isFP = true; } // FirstPerson
			if (glfwGetKey(window, GLFW_KEY_A)) { // A
				//app.isMoving = true;
				if (angle < 90.0f) {
					app.fpTarget.x += 1;
					app.fpTarget.z -= 1;
					timer = 0;
				}
				if (angle < 180.0f) {
					app.fpTarget.x -= 1;
					app.fpTarget.z -= 1;
					timer = 0;
				}
				if (angle < 270.0f) {
					app.fpTarget.x -= 1;
					app.fpTarget.z += 1;
					timer = 0;
				}
				if (angle < 0.0f) {
					app.fpTarget.x -= 1;
					app.fpTarget.z += 1;
					timer = 0;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_W)) { // W
				//app.isMoving = true; 
				app.fpEye.x += (app.fpTarget.x - app.fpEye.x) * vel;
				app.fpEye.z += (app.fpTarget.z - app.fpEye.z) * vel;
				app.fpTarget.x += (app.fpTarget.x + app.fpEye.x) * vel;
				app.fpTarget.z += (app.fpTarget.z - app.fpEye.z) * vel;
			}
			else if (glfwGetKey(window, GLFW_KEY_S)) { // S
				app.fpEye.x -= (app.fpTarget.x - app.fpEye.x) * vel;
				app.fpEye.z -= (app.fpTarget.z - app.fpEye.z) * vel;
				app.fpTarget.x -= (app.fpTarget.x - app.fpEye.x) * vel;
				app.fpTarget.z -= (app.fpTarget.z - app.fpEye.z) * vel;
			}
			else if (glfwGetKey(window, GLFW_KEY_D)) { // D
				//app.isMoving = true;
				app.fpEye.x -= (app.fpTarget.x - app.fpEye.x) * vel;
				app.fpTarget.x -= (app.fpTarget.x - app.fpEye.x) * vel;
				timer = 0;
			}
		} // if
	}
	glfwTerminate(); // Close GL context and any other GLFW resources
	return 0;
}

void glfwGetCursorPosition(GLFWwindow *window, double *x, double *y) {
	app.mouseCursor(*x, *y);
}

void glfwGetMouseButton(GLFWwindow *window, int *button) {
	app.mouseButton(*button);
}

void glfwGetMousePos(int x, int y) {
	xpos = x;
	ypos = y;
}

void glfwSetMousePos(int sX, int sY) {
	xpos = sX;
	ypos = sY;
}