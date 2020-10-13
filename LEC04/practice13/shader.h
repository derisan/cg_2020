// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <string>

#include <glm/glm.hpp>

using GLenum = unsigned int;
using GLuint = unsigned int;

class Shader
{
public:
	Shader();
	~Shader();
	
	bool Load(const std::string& vertName, const std::string& fragName);
	void SetActive();
	
	void SetMatrixUniform(const std::string& name, const glm::mat4& mat);
	void SetVectorUniform(const std::string& name, const glm::vec3& vec);
	void SetFloatUniform(const std::string& name, float value);

private:
	
	bool CompileShader(const std::string& fileName,
					   GLenum shaderType,
					   GLuint& outShader);
	
	
	bool IsCompiled(GLuint shader);
	
	bool IsValidProgram();
private:
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
