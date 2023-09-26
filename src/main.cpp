/* hello.c */
#include <stdio.h>
#include <iostream>
#include "GLFW/glfw3.h"

int main(void) {

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	while (true) {

	}

	glfwDestroyWindow(window);

	//puts("Hello, world!");
	return 0;
}