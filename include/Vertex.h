#ifndef VERTEX
#define VERTEX 

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;
};

#endif
