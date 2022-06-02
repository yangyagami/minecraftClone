#include "glad/glad.h"
#include "Texture.h" 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Opengl {
	Texture::Texture(string path) {
		unsigned char *data = loadImage(path);

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, id);
	}

	unsigned char *Texture::loadImage(string path) {
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		return data;
	}

	int Texture::getWidth() {
		return width;
	}

	int Texture::getHeight() {
		return height;
	}

	Texture::~Texture() {
			
	}
}
