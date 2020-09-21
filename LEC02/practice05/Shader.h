#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

class Shader
{
public:
	Shader();
	~Shader();
		
	bool load(const std::string& vertName, const std::string& fragName);
	void unload();
	
	void use();
	void setMatrixUniform(const char* name, const glm::mat4& matrix);

	void setMat4(const std::string& name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
	}

	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
	}

	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
	}

private:
	bool compileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	bool isCompiled(GLuint shader);
	bool isValidProgram();

private:
	GLuint _vertexShader;
	GLuint _fragShader;
	GLuint _shaderProgram;
};

Shader* createShader(const std::string& vert, const std::string& frag);