#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Buffer.h"
#include "VertexArray.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Input.h"
#include "Texture.h"
#include "Chunk.h"


int main() {
	const int winWidth = 800;
	const int winHeight = 600;

	/*
	 *            
	 *           v6/--------/v5
	 *            / |      / |
	 *           /  |     /  |
	 *         v0   |    v1  |
	 *          | v7-----|---/v4
	 *          |  /     |  /
	 *          | /      | /
	 *          |/       |/
	 *         v2--------v3
	 *         
	 *     front:  v0, v1, v2, v3
	 *	   back:   v6, v5, v7, v4 
	 *     left:   v6, v0, v7, v2
	 *     right:  v5, v1, v4, v3
	 *     top:    v6, v5, v0, v1
	 *     bottom: v7, v4, v2, v3
	 * */
	float vertices[] = {
		-1.0f,  1.0f,  1.0f,    1.0f,  1.0f,  1.0f,    -1.0f, -1.0f,  1.0f,     1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,    1.0f,  1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,     1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,   -1.0f,  1.0f,  1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,    1.0f,  1.0f,  1.0f,     1.0f, -1.0f, -1.0f,     1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,    1.0f,  1.0f, -1.0f,    -1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,     1.0f, -1.0f,  1.0f,
	};

	float texCoords[] = {
		0.0f, 1.0f,			1.0f / 3.0f, 1.0f,  0.0f, 0.0f,			1.0f / 3.0f, 0.0f,
		0.0f, 1.0f,  		1.0f / 3.0f, 1.0f,  0.0f, 0.0f,  		1.0f / 3.0f, 0.0f,
		0.0f, 1.0f,  		1.0f / 3.0f, 1.0f,  0.0f, 0.0f,  		1.0f / 3.0f, 0.0f,
		0.0f, 1.0f,  		1.0f / 3.0f, 1.0f,  0.0f, 0.0f,  		1.0f / 3.0f, 0.0f,
		1.0f / 3.0f, 1.0f,  2.0f / 3.0f, 1.0f,  1.0f / 3.0f, 0.0f,  2.0f / 3.0f, 0.0f,
		2.0f / 3.0f, 1.0f,  1.0f, 1.0f,         2.0f / 3.0f, 0.0f,  1.0f, 0.0f,
	};

	unsigned int indices[] = {
		0,  1, 2,  2,  3,  1,
		4,  5, 6,  6,  7,  5,
		8,  9, 10, 10, 11, 9,
		12, 13,14, 14, 15, 13,
		16, 17,18, 18, 19, 17,
		20, 21,22, 22, 23, 21,
	};

	Window window("Minecraft", winWidth, winHeight);

	glEnable(GL_DEPTH_TEST);

	//do something opengl stuff
	Chunk::initBlocks();

	Chunk *chunks[49];

	int index = 0;

	for (int x = -3; x <= 3; x++) {
		for (int z = -3; z <= 3; z++) {
			chunks[index] = new Chunk(x, z);
			index++;
		}
	}

	Opengl::Shader shader("shader/vertex.glsl", "shader/fragment.glsl");

	Camera camera(glm::vec3(0.0f, 200.0f, 0.0f));

	glm::mat4 view = camera.getView();
	glm::mat4 proj = camera.getProjection();

	shader.setMat4f("projection", proj);

	shader.setMat4f("view", view);

	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间
	
	Input::init();

	glm::vec3 &cameraPos = camera.getPosition();
	glm::vec3 &cameraFront = camera.getFront();
	glm::vec3 &cameraUp = camera.getUp();

	float lastX = 400, lastY = 300;
	float pitch = 0.0f;
	float yaw = 0.0f;

	while (!window.shouldClose()) {
        glClearColor(141.0f / 255.0f, 227.0f / 255.0f, 224.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::vec2 m = Input::getMousePos();

		float xoffset = m.x - lastX;
		float yoffset = lastY - m.y;
		lastX = m.x;
		lastY = m.y;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
    	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    	front.y = sin(glm::radians(pitch));
    	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    	cameraFront = glm::normalize(front);

		if (Input::isKeyPressed(GLFW_KEY_W)) {
			cameraPos += 0.5f * cameraFront;
		}	
		if (Input::isKeyPressed(GLFW_KEY_S)) {
			cameraPos -= 0.5f * cameraFront;
		}	
		if (Input::isKeyPressed(GLFW_KEY_A)) {
			cameraPos -= 0.5f * glm::normalize(glm::cross(cameraFront, cameraUp));
		}	
		if (Input::isKeyPressed(GLFW_KEY_D)) {
			cameraPos += 0.5f * glm::normalize(glm::cross(cameraFront, cameraUp));
		}	

		view = camera.getView();
		shader.setMat4f("view", view);

		for (int i = 0; i < 49; i++) {
			chunks[i]->render();
		}

	
		window.update();
	}

	return 0;
}
