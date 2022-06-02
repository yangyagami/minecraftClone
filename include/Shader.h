#ifndef OPENGL_SHADER
#define OPENGL_SHADER

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace Opengl {
	
	class Shader {
		private:
			unsigned int id;
		private:
			unsigned int compileShader(int type, string source);
			string readFile(string file);
		public:
			Shader(string vertexShaderSource, string fragmentShaderSource);
			void bind();
			void setMat4f(string name, glm::mat4 &data);
			~Shader();
	};

};

#endif

