#pragma once

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;


class Shader
{
public:

	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	~Shader();
	void use();
	void setMat4(const string& name, const glm::mat4& mat);
	void setVec3(const string& name, const float x, const float y, const float z);
	void setVec3(const string& name, const glm::vec3& value);
	void setFloat(const string& name, const float &value);
	void setInt(const string& name, const int value);
private:
	string vertexString;
	string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	void checkCompileErrors(unsigned int ID, string type);
};


