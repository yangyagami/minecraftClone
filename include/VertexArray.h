#ifndef OPENGL_VERTEX_ARRAY
#define OPENGL_VERTEX_ARRAY

#include <cstddef>

namespace Opengl {

	class VertexArray {
		private:
			unsigned int id;
		public:
			VertexArray();
			void bind();
			void setVertexAttribPointer(unsigned int index, int size, int type, int normalized, size_t stride, const void *pointer); 
			~VertexArray();
	};

}

#endif
