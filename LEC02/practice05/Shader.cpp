#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
	: _shaderProgram(0)
	, _vertexShader(0)
	, _fragShader(0)
{
}

Shader::~Shader()
{
}

bool Shader::load(const std::string& vertName, const std::string& fragName)
{
	if (!compileShader(vertName,
		GL_VERTEX_SHADER,
		_vertexShader) ||
		!compileShader(fragName,
			GL_FRAGMENT_SHADER,
			_fragShader))
	{
		return false;
	}

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragShader);
	glLinkProgram(_shaderProgram);

	glDeleteShader(_vertexShader);
	glDeleteShader(_fragShader);

	if (!isValidProgram())
		return false;
	

	return true;
}

void Shader::unload()
{
	glDeleteProgram(_shaderProgram);
}

void Shader::use()
{
	glUseProgram(_shaderProgram);
}

bool Shader::compileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!isCompiled(outShader))
		{
			
			return false;
		}
	}
	else
	{
		std::cout << "Shader file not found: " << fileName.c_str() << '\n';
		return false;
	}

	return true;
}

bool Shader::isCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		std::cout << "GLSL Compile Failed: " << buffer << '\n';
		return false;
	}

	return true;
}

bool Shader::isValidProgram()
{

	GLint status;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(_shaderProgram, 511, nullptr, buffer);
		std::cout << "GLSL Link Status: " << buffer << '\n';
		return false;
	}

	return true;
}

Shader* createShader(const std::string& vert, const std::string& frag)
{
	Shader* sp(new Shader());
	sp->load(vert, frag);

	return sp;
}