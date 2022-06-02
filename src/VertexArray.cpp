#include "VertexArray.h"
#include "glad/glad.h"

namespace Opengl {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &id);
		glBindVertexArray(id);
	}

	VertexArray::~VertexArray() {
		glBindVertexArray(0);
	}

	void VertexArray::bind() {
		glBindVertexArray(id);
	}

	void VertexArray::setVertexAttribPointer(unsigned int index, int size, int type, int normalized, size_t stride, const void *pointer) {
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
	}

}
