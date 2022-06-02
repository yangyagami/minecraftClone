#include "Chunk.h"
#include "Texture.h"
#include "Window.h"
#include "Buffer.h"
#include <iostream>
#include <utility>

using namespace std;

vector<Block> Chunk::blocks;
Opengl::Texture *Chunk::texture = nullptr;

Chunk::Chunk(int px, int pz) : LENGTH(16), WIDTH(16), HEIGHT(256) {
	mx = px * LENGTH;
	mz = pz * WIDTH;

	vertexSize = 0;

	data = new int[LENGTH * WIDTH * HEIGHT];
	vertices = new Vertex[LENGTH * WIDTH * HEIGHT * 24];
	indices = new unsigned int[LENGTH * WIDTH * HEIGHT * 36];	

	for (int i = 0; i < LENGTH * WIDTH * HEIGHT; i++) {
		data[i] = rand() % 2 - 1;
	}

	int i = 0;
	int currentIndex = 0;
	for (int x = 0; x < LENGTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int z = 0; z < WIDTH; z++) {
				int index = (x * HEIGHT * WIDTH + y * WIDTH + z) * 24;
				int dataIndex = x * HEIGHT * WIDTH + y * WIDTH + z;
				int blockID = data[dataIndex];
				Block block;

				if (blockID != -1) {
					block = blocks[blockID];
				}

				glm::vec3 pos((x + mx) * 2.0f, y * 2.0f, (z + mz) * 2.0f);

				//front
				if (blockID != -1 && (z == WIDTH - 1 || z + 1 < WIDTH && data[x * HEIGHT * WIDTH + y * WIDTH + z + 1] != 0)) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z + 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[0];
					vertices[(currentIndex + 1)].uv = block.uv[1];
					vertices[(currentIndex + 2)].uv = block.uv[2];
					vertices[(currentIndex + 3)].uv = block.uv[3];

					vertices[(currentIndex + 0)].normal = glm::vec3(0.0f, 0.0f, 1.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(0.0f, 0.0f, 1.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(0.0f, 0.0f, 1.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(0.0f, 0.0f, 1.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

				//back
				if (blockID != -1 && (z == 0 || (z - 1 >= 0 && data[x * HEIGHT * WIDTH + y * WIDTH + z - 1] != 0))) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z - 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[4];
					vertices[(currentIndex + 1)].uv = block.uv[5];
					vertices[(currentIndex + 2)].uv = block.uv[6];
					vertices[(currentIndex + 3)].uv = block.uv[7];

					vertices[(currentIndex + 0)].normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(0.0f, 0.0f, -1.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(0.0f, 0.0f, -1.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

				//left 
				if (blockID != -1 && (x == 0 || x - 1 >= 0 && data[(x - 1) * HEIGHT * WIDTH + y * WIDTH + z] != 0)) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z + 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[8];
					vertices[(currentIndex + 1)].uv = block.uv[9];
					vertices[(currentIndex + 2)].uv = block.uv[10];
					vertices[(currentIndex + 3)].uv = block.uv[11];

					vertices[(currentIndex + 0)].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

				//right 
				if (blockID != -1 && (x == LENGTH - 1 || x + 1 < LENGTH && data[(x + 1) * HEIGHT * WIDTH + y * WIDTH + z] != 0)) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z + 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[12];
					vertices[(currentIndex + 1)].uv = block.uv[13];
					vertices[(currentIndex + 2)].uv = block.uv[14];
					vertices[(currentIndex + 3)].uv = block.uv[15];

					vertices[(currentIndex + 0)].normal = glm::vec3(1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(1.0f, 0.0f, 0.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(1.0f, 0.0f, 0.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

				//top
				if (blockID != -1 && (y == HEIGHT - 1 || y + 1 <= HEIGHT - 1 && data[x * HEIGHT * WIDTH + (y + 1) * WIDTH + z] != 0)) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x - 1.0f, pos.y + 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[16];
					vertices[(currentIndex + 1)].uv = block.uv[17];
					vertices[(currentIndex + 2)].uv = block.uv[18];
					vertices[(currentIndex + 3)].uv = block.uv[19];

					vertices[(currentIndex + 0)].normal = glm::vec3(0.0f, 1.0f, 0.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(0.0f, 1.0f, 0.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(0.0f, 1.0f, 0.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(0.0f, 1.0f, 0.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

				//bottom 
				if (blockID != -1 && (y == 0 || y - 1 >= 0 && data[x * HEIGHT * WIDTH + (y - 1) * WIDTH + z] != 0)) {
					vertices[(currentIndex + 0)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 1)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z - 1.0f);
					vertices[(currentIndex + 2)].pos = glm::vec3(pos.x - 1.0f, pos.y - 1.0f, pos.z + 1.0f);
					vertices[(currentIndex + 3)].pos = glm::vec3(pos.x + 1.0f, pos.y - 1.0f, pos.z + 1.0f);

					vertices[(currentIndex + 0)].uv = block.uv[20];
					vertices[(currentIndex + 1)].uv = block.uv[21];
					vertices[(currentIndex + 2)].uv = block.uv[22];
					vertices[(currentIndex + 3)].uv = block.uv[23];

					vertices[(currentIndex + 0)].normal = glm::vec3(0.0f, -1.0f, 0.0f);
					vertices[(currentIndex + 1)].normal = glm::vec3(0.0f, -1.0f, 0.0f);
					vertices[(currentIndex + 2)].normal = glm::vec3(0.0f, -1.0f, 0.0f);
					vertices[(currentIndex + 3)].normal = glm::vec3(0.0f, -1.0f, 0.0f);

					indices[i + 0] = 0 + currentIndex;
					indices[i + 1] = 1 + currentIndex;
					indices[i + 2] = 2 + currentIndex;

					indices[i + 3] = 2 + currentIndex;
					indices[i + 4] = 3 + currentIndex;
					indices[i + 5] = 1 + currentIndex;

					currentIndex += 4;
					i += 6;
					vertexSize += 6;
				}

			}
		}
	}

	vao = new Opengl::VertexArray();
	vao->bind();

	vbo = new Opengl::Buffer(GL_ARRAY_BUFFER, LENGTH * WIDTH * HEIGHT * 24 * sizeof(Vertex), vertices, GL_DYNAMIC_DRAW);
	vbo->bind();

	ibo = new Opengl::Buffer(GL_ELEMENT_ARRAY_BUFFER, LENGTH * WIDTH * HEIGHT * 36 * sizeof(unsigned), indices, GL_DYNAMIC_DRAW);
	ibo->bind();

	vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	vao->setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao->setVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
}

void Chunk::initBlocks() {
	if (texture == nullptr) {
		texture = new Opengl::Texture("test.png");
	}
	float width = texture->getWidth() * 1.0f;
	float height = texture->getHeight() * 1.0f;

	float cellSize = 32.0f;

	Block grass;
	grass.id = 0;
	grass.name = "grass";

	grass.uv[0] = glm::vec2(0.0f, cellSize / height);
	grass.uv[1] = glm::vec2(cellSize / width, cellSize / height);
	grass.uv[2] = glm::vec2(0.0f, 0.0f);
	grass.uv[3] = glm::vec2(cellSize / width, 0.0f);

	grass.uv[4] = glm::vec2(0.0f, cellSize / height);
	grass.uv[5] = glm::vec2(cellSize / width, cellSize / height);
	grass.uv[6] = glm::vec2(0.0f, 0.0f);
	grass.uv[7] = glm::vec2(cellSize / width, 0.0f);

	grass.uv[8]  = glm::vec2(0.0f, cellSize / height);
	grass.uv[9]  = glm::vec2(cellSize / width, cellSize / height);
	grass.uv[10] = glm::vec2(0.0f, 0.0f);
	grass.uv[11] = glm::vec2(cellSize / width, 0.0f);

	grass.uv[12] = glm::vec2(0.0f, cellSize / height);
	grass.uv[13] = glm::vec2(cellSize / width, cellSize / height);
	grass.uv[14] = glm::vec2(0.0f, 0.0f);
	grass.uv[15] = glm::vec2(cellSize / width, 0.0f);

	grass.uv[16] = glm::vec2(cellSize / width, cellSize / height);
	grass.uv[17] = glm::vec2(cellSize * 2 / width, cellSize / height);
	grass.uv[18] = glm::vec2(cellSize / width, 0.0f);
	grass.uv[19] = glm::vec2(cellSize * 2 / width, 0.0f);

	grass.uv[20] = glm::vec2(cellSize * 2 / width, cellSize / height);
	grass.uv[21] = glm::vec2(cellSize * 3 / width, cellSize / height);
	grass.uv[22] = glm::vec2(cellSize * 2 / width, 0.0f);
	grass.uv[23] = glm::vec2(cellSize * 3 / width, 0.0f);

	blocks.push_back(grass);
}

void Chunk::render() {
	vao->bind();
	texture->bind();
	glDrawElements(GL_TRIANGLES, vertexSize, GL_UNSIGNED_INT, nullptr);
}

void Chunk::destory() {
	delete texture;
}

Chunk::~Chunk() {
	delete[] data;
	delete[] vertices;
	delete[] indices;
	delete vao;
	delete vbo;
	delete ibo;
}

