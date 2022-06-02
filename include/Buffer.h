#ifndef OPENGL_BUFFER
#define OPENGL_BUFFER

#include "glad/glad.h"
#include <cstddef>

namespace Opengl {
	
	class Buffer {
		private:
			unsigned int id;
			int mTarget;
		public:
			Buffer(int target, size_t size, void *data, int usage);
			void bind();
			~Buffer();
	};

}

#endif
