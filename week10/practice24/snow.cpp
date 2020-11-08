#include "snow.h"

#include <GL/glew.h>

#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "vertexarray.h"
#include "mesh.h"
#include "random.h"

Snow::Snow(Game* game)
	: Actor{ game },
	mMesh{ nullptr },
	mVelocity{ 0.0f, 0.0f, 0.0f },
	mGravity{ Random::GetFloatRange(-1.0f, -0.1f), Random::GetFloatRange(-2.0f, -0.5f), 0.0f }
{
	game->GetSnows().emplace_back(this);

	auto renderer = Renderer::Get();
	mMesh = new Mesh{};
	mMesh = renderer->GetMesh("Assets/sphere.gpmesh");

	SetScale(0.005f);

	SetPosition(glm::vec3{ Random::GetFloatRange(0.0f, 4.0f), 5.0f, Random::GetFloatRange(-4.0f, 0.0f) });
}

void Snow::UpdateActor()
{
	Actor::UpdateActor();

	mVelocity += mGravity * dt;
	auto pos = GetPosition() + mVelocity * dt;

	if (pos.y < 0.0f)
		SetState(State::kDead);

	SetPosition(pos);
}

void Snow::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrix4Uniform("uWorld", GetWorldTransform());
	mMesh->GetTexture()->SetActive();
	auto vertexArray = mMesh->GetVertexArray();
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}