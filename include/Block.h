#ifndef BLOCK 
#define BLOCK 

#include <glm/ext/vector_float2.hpp>
#include <string>
using namespace std;

struct Block {
	unsigned int id;
	string name;
	glm::vec2 uv[24];
};

#endif
