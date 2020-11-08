#include "background.h"

#include <GL/glew.h>

#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "vertexarray.h"
#include "mesh.h"

Background::Background(Game* game)
	: Actor{ game },
	mMesh{ nullptr }
{
	auto renderer = Renderer::Get();

	mMesh = new Mesh{};
	mMesh = renderer->GetMesh("Assets/zima.gpmesh");

	SetScale(0.5f);
	SetRotation(180.0f);
	SetPosition(glm::vec3{ 3.0f, -1.0f, 0.0f });
}

void Background::Draw(Shader* shader)
{
	shader->SetMatrix4Uniform("uWorld", GetWorldTransform());
	mMesh->GetTexture()->SetActive();
	auto vertexArray = mMesh->GetVertexArray();
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

