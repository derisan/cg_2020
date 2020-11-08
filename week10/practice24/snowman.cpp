#include "snowman.h"

#include <GL/glew.h>

#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "vertexarray.h"
#include "mesh.h"

Snowman::Snowman(Game* game)
	: Actor{ game },
	mMesh{ nullptr }
{
	auto renderer = Renderer::Get();
	mMesh = new Mesh{};
	mMesh = renderer->GetMesh("Assets/snowman.gpmesh");

	SetRotation(90.0f);
	SetScale(0.5f);
	SetPosition(glm::vec3{ 0.0f, 0.0f, -1.0f });
}

void Snowman::Draw(Shader* shader)
{
	shader->SetMatrix4Uniform("uWorld", GetWorldTransform());
	mMesh->GetTexture()->SetActive();
	auto vertexArray = mMesh->GetVertexArray();
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}