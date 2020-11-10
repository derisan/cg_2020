#include "background.h"

#include <GL/glew.h>

#include "game.h"

#include "vertexarray.h"
#include "texture.h"
#include "shader.h"
#include "renderer.h"

Background::Background(Game* game)
	: Actor{ game },
	mTexture{ nullptr },
	mVertexArray{ nullptr },
	mShader{ nullptr }
{
	auto renderer = Renderer::Get();

	mTexture = renderer->GetTexture("Assets/bg.jpg");
	mShader = renderer->GetShader("bg");

	Load();

	SetScale(20.0f);
}

void Background::Draw(Shader* shader)
{
	mShader->SetActive();
	mTexture->SetActive();
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

	// Disable bg shader
	shader->SetActive();
}

void Background::Load()
{
	const float vertices[] = {
		// pos				// tex
		-1.0f, 1.0f, 0.99f,  0.0f, 1.0f,
		-1.0f,-1.0f, 0.99f,	0.0f, 0.0f,
		1.0f, -1.0f, 0.99f,  1.0f, 0.0f,
		1.0f, 1.0f,  0.99f,   1.0f, 1.0f
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
}