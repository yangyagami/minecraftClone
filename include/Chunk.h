#ifndef CHUNK
#define CHUNK 

#include <glm/ext/vector_float3.hpp>
#include "Block.h"
#include <vector>
#include "Vertex.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Texture.h"

using namespace std;

class Chunk {
	private:
		const int LENGTH;
		const int WIDTH;
		const int HEIGHT;
		int *data;
		Vertex *vertices;
		unsigned int *indices;
		Opengl::Buffer *vbo;
		Opengl::Buffer *ibo;
		Opengl::VertexArray *vao;
		int mx;
		int mz;
		int vertexSize;
	private:
		static Opengl::Texture *texture;
		static vector<Block> blocks;
	public:
		Chunk(int px, int pz);
		void render();
		void destory();
		~Chunk();
	public:
		static void initBlocks();
};

#endif
