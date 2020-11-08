#include "cube.h"

#include <GL/glew.h>

#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "vertexarray.h"
#include "mesh.h"

Cube::Cube(Game* game)
	: Actor{ game },
	mMesh{ nullptr },
	mShader{ nullptr }
{
	auto renderer = Renderer::Get();
	mMesh = new Mesh{};
	mMesh = renderer->GetMesh("Assets/cube.gpmesh");
	mShader = renderer->GetShader("mesh");

	SetScale(0.02f);
}

void Cube::Draw(Shader* shader)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mShader->SetActive();
	mShader->SetMatrix4Uniform("uWorld", GetWorldTransform());
	mMesh->GetTexture()->SetActive();
	auto vertexArray = mMesh->GetVertexArray();
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

	glDisable(GL_BLEND);
}