#include "Buffer.h"

namespace Opengl {

	Buffer::Buffer(int target, size_t size, void *data, int usage) {
		mTarget = target;
		glGenBuffers(1, &id);
		glBindBuffer(mTarget, id); 
		glBufferData(mTarget, size, data, usage);
	}

	void Buffer::bind() {
		glBindBuffer(mTarget, id);
	}

	Buffer::~Buffer() {
		glBindBuffer(mTarget, 0);
	}

}
