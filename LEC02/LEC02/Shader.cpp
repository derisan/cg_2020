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
	// Compile vertex and pixel shaders
	if (!compileShader(vertName,
		GL_VERTEX_SHADER,
		_vertexShader) ||
		!compileShader(fragName,
			GL_FRAGMENT_SHADER,
			_fragShader))
	{
		return false;
	}

	// Now create a shader program that
	// links together the vertex/frag shaders
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragShader);
	glLinkProgram(_shaderProgram);

	glDeleteShader(_vertexShader);
	glDeleteShader(_fragShader);

	// Verify that the program linked successfully
	if (!isValidProgram())
	{
		return false;
	}

	return true;
}

void Shader::unload()
{
	// Delete the program/shaders
	glDeleteProgram(_shaderProgram);
}

void Shader::use()
{
	// Set this program as the active one
	glUseProgram(_shaderProgram);
}

void Shader::setMatrixUniform(const char* name, const glm::mat4& matrix)
{
	// Find the uniform by this name
	GLuint loc = glGetUniformLocation(_shaderProgram, name);
	// Send the matrix data to the uniform
	glUniformMatrix4fv(loc, 1, GL_TRUE, &matrix[0][0]);
}

bool Shader::compileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	// Open file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// Read all the text into a string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// Create a shader of the specified type
		outShader = glCreateShader(shaderType);
		// Set the source characters and try to compile
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
	// Query the link status
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