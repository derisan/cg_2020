#pragma once
#include <string>
#include <glm/glm.hpp>

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