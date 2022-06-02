#include "Camera.h" 
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos) {
	mPos = pos;
	front = glm::vec3(0.0f, 0.0f, -1.0f);	
	up = glm::vec3(0.0f, 1.0f,  0.0f);
}

glm::mat4 Camera::getView() {
	return glm::lookAt(mPos, mPos + front, up);
}

glm::mat4 Camera::getProjection() {
	return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 200.0f);
}

glm::vec3 &Camera::getPosition() {
	return mPos;
}

glm::vec3 &Camera::getFront() {
	return front;
}

glm::vec3 &Camera::getUp() {
	return up;
}

