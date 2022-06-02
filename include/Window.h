#ifndef GLFW_WINDOW
#define GLFW_WINDOW

#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class Window {
	private:
		GLFWwindow *glfwWindow;
		int mWidth;
		int mHeight;
		static Window *instance;
	public:
		Window(string title, int width, int height);
		void update();
		bool shouldClose();
		static Window *getInstance();
		int getWidth();
		int getHeight();
		GLFWwindow *getGlfwWindow();
		~Window();
};

#endif
