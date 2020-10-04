#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
	: shader_program_(0)
	, vertex_shader_(0)
	, frag_shader_(0)
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	if (!CompileShader(vertName,
		GL_VERTEX_SHADER,
		vertex_shader_) ||
		!CompileShader(fragName,
			GL_FRAGMENT_SHADER,
			frag_shader_))
	{
		return false;
	}

	shader_program_ = glCreateProgram();
	glAttachShader(shader_program_, vertex_shader_);
	glAttachShader(shader_program_, frag_shader_);
	glLinkProgram(shader_program_);

	glDeleteShader(vertex_shader_);
	glDeleteShader(frag_shader_);

	if (!IsValidProgram())
		return false;
	

	return true;
}

void Shader::Unload()
{
	glDeleteProgram(shader_program_);
}

void Shader::SetActive()
{
	glUseProgram(shader_program_);
}

bool Shader::CompileShader(const std::string& fileName,
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

		if (!IsCompiled(outShader))
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

bool Shader::IsCompiled(GLuint shader)
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

bool Shader::IsValidProgram()
{

	GLint status;
	glGetProgramiv(shader_program_, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(shader_program_, 511, nullptr, buffer);
		std::cout << "GLSL Link Status: " << buffer << '\n';
		return false;
	}

	return true;
}

Shader* CreateShader(const std::string& vert, const std::string& frag)
{
	Shader* sp(new Shader());
	if (!sp->Load(vert, frag))
	{
		sp->Unload();
		delete sp;

		sp = nullptr;
	}

	return sp;
}