#ifndef OPENGL_TEXTURE
#define OPENGL_TEXTURE

#include <string>
using namespace std;

namespace Opengl {

	class Texture {
		private:
			unsigned int id;
			int width, height, channels;
		private:
			unsigned char *loadImage(string path);
		public:
			Texture(string path);
			void bind();
			int getWidth();
			int getHeight();
			~Texture();
	};

}

#endif
