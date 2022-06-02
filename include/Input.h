#ifndef INPUT
#define INPUT 

#include "Window.h"
#include <glm/ext/vector_float2.hpp>

class Input {
	private:
		static GLFWwindow *window;
	public:
		static void init();
		static bool isKeyPressed(int key);
		static glm::vec2 getMousePos();

};

#endif
