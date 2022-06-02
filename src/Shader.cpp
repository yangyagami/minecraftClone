#include "Shader.h"
#include "glad/glad.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace Opengl {

	Shader::Shader(string vertexShader, string fragmentShader) {
		string vertexShaderSource = readFile(vertexShader);
		string fragmentShaderSource = readFile(fragmentShader);
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		id = glCreateProgram();
		glAttachShader(id, vs);
		glAttachShader(id, fs);
		glLinkProgram(id);

		glUseProgram(id);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	unsigned int Shader::compileShader(int type, string source) {
		unsigned int sourceID;
		const char *sourcePtr = source.c_str();
		sourceID = glCreateShader(type);
		glShaderSource(sourceID, 1, &sourcePtr, nullptr);
		glCompileShader(sourceID);

		return sourceID;
	}

	void Shader::bind() {
		glUseProgram(id);
	}

	void Shader::setMat4f(string name, glm::mat4 &data) {
		unsigned int location = glGetUniformLocation(id, name.c_str());	
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
	}

	string Shader::readFile(string file) {
		string data = "";		
		ifstream f;
		f.open(file);

		while (!f.eof()) {
			string temp = "";
			getline(f, temp);
			temp += '\n';
			data += temp;
		}

		return data;
	}

	Shader::~Shader() {
		glDeleteProgram(id);
	}

}
