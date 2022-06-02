#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	private:
		glm::vec3 mPos;
		glm::vec3 front;
		glm::vec3 up;		
	public:
		Camera(glm::vec3 pos);
		glm::mat4 getView();
		glm::mat4 getProjection();
		glm::vec3 &getPosition();
		glm::vec3 &getFront();
		glm::vec3 &getUp();
};

#endif
