#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
		
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	
	void SetActive();
	
	void SetMat4(const std::string& name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_program_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shader_program_, name.c_str()), 1, glm::value_ptr(value));
	}

	void SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shader_program_, name.c_str()), x, y, z);
	}

private:
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

private:
	GLuint vertex_shader_;
	GLuint frag_shader_;
	GLuint shader_program_;
};

Shader* CreateShader(const std::string& vert, const std::string& frag);