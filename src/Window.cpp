#include "glad/glad.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

Window *Window::instance = nullptr;

Window::Window(string title, int width, int height) : mWidth(width), mHeight(height) {
	instance = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (glfwWindow == nullptr) {
	    cout << "Failed to create GLFW window" << endl;
	    glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(glfwWindow);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		exit(0);
	}

	glViewport(0, 0, width, height);
}

void Window::update() {
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();    
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(glfwWindow);
}

GLFWwindow *Window::getGlfwWindow() {
	return glfwWindow;
}

Window *Window::getInstance() {
	return instance;
}

int Window::getWidth() {
	return mWidth;
}

int Window::getHeight() {
	return mHeight;
}

Window::~Window() {
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}
