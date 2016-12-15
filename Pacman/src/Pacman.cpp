#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;
int screenX = 640; int screenY = 480;
int xpos, ypos;

void keyBoard(GLFWwindow *window, int key, int scancode, int action, int mods) {
	app.keyBoard(key, scancode, action, mods);
}

void mousePos(GLFWwindow *window, double x, double y) {
	app.mouseCursor(x, y);
}

void mouseClic(GLFWwindow *window, int button, int action, int mods) {
	app.mouseButton(button, action, mods);
}

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

	glfwSetKeyCallback(window, keyBoard);
	glfwSetCursorPosCallback(window, mousePos);
	glfwSetMouseButtonCallback(window, mouseClic);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents(); // Update other events like input handling
		app.update(); // Update de Application
		app.display(); // Put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}
	glfwTerminate(); // Close GL context and any other GLFW resources
	return 0;
}