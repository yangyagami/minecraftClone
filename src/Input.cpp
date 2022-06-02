#include "Input.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>

GLFWwindow *Input::window = nullptr;

void Input::init() {
	window = Window::getInstance()->getGlfwWindow();
}

bool Input::isKeyPressed(int key) {
	return glfwGetKey(window, key); 
}

glm::vec2 Input::getMousePos() {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return glm::vec2(x, y); 
}
