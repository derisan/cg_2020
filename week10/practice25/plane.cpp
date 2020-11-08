#include "plane.h"

#include <GL/glew.h>

#include "game.h"

#include "vertexarray.h"
#include "texture.h"
#include "shader.h"
#include "renderer.h"

Plane::Plane(Game* game, Type type)
	: Actor{ game },
	mTexture{ nullptr },
	mVertexArray{ nullptr },
	mType{ type },
	mRotationSpeed{ 0.0f }
{
	Load();
}

void Plane::ActorInput(unsigned char key)
{
	Actor::ActorInput(key);

	if (key == 'x' || key == 'X')
		SetAxis(glm::vec3{ 1.0f, 0.0f, 0.0f });

	else if (key == 'y' || key == 'Y')
		SetAxis(glm::vec3{ 0.0f, 1.0f, 0.0f });
}

void Plane::UpdateActor()
{
	Actor::UpdateActor();

	mRotationSpeed += dt * 30;

	SetRotation(mRotationSpeed);
}

void Plane::Draw(Shader* shader)
{
	if (GetState() == State::kPaused)
		return;

	shader->SetMatrix4Uniform("uWorld", GetWorldTransform());
	mTexture->SetActive();
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Plane::Load()
{
	auto renderer = Renderer::Get();
	if (mType == Type::kTop)
	{
		mTexture = renderer->GetTexture("Assets/a.png");

		const float vertices[] = {
			// pos				// tex
			-0.5f, 0.5f, -0.5f,	0.0f, 1.0f,
			-0.5f, 0.5f, 0.5f,	0.0f, 0.0f,
			0.5f, 0.5f, 0.5f,   1.0f, 0.0f,
			0.5f, 0.5f, -0.5f,  1.0f, 1.0f
		};

		const unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		mVertexArray = new VertexArray{vertices, 4, indices, 6};
	}
	else if (mType == Type::kBottom)
	{
		mTexture = renderer->GetTexture("Assets/b.png");

		const float vertices[] = {
			// pos				// tex
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,	// top left
			-0.5f, -0.5f, 0.5f,	 0.0f, 1.0f,	// bottom left
			0.5f, -0.5f, 0.5f,   1.0f, 1.0f,	// bottom right
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f		// top right
		};

		const unsigned int indices[] = {
			0, 2, 1,
			0, 3, 2
		};

		mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
	}
	else if (mType == Type::kLeft)
	{
		mTexture = renderer->GetTexture("Assets/c.png");

		const float vertices[] = {
			// pos				// tex
			-0.5f, 0.5f, 0.5f,   1.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,	 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f,  0.0f, 1.0f
		};

		const unsigned int indices[] = {
			0, 2, 1,
			0, 3, 2
		};

		mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
	}
	else if (mType == Type::kRight)
	{
		mTexture = renderer->GetTexture("Assets/d.png");

		const float vertices[] = {
			// pos				// tex
			0.5f, 0.5f, 0.5f,   0.0f, 1.0f,
			0.5f, -0.5f, 0.5f,	0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f,  1.0f, 1.0f
		};

		const unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
	}
	else if (mType == Type::kFront)
	{
		mTexture = renderer->GetTexture("Assets/e.png");

		const float vertices[] = {
			// pos				// tex
			-0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
			-0.5f,-0.5f, 0.5f,	0.0f, 0.0f,
			0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
			0.5f, 0.5f, 0.5f,   1.0f, 1.0f
		};

		const unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
	}
	else 
	{
		mTexture = renderer->GetTexture("Assets/f.png");

		const float vertices[] = {
			// pos				// tex
			-0.5f, 0.5f, -0.5f,   1.0f, 1.0f,
			-0.5f,-0.5f, -0.5f,	  1.0f, 0.0f,
			0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
			0.5f, 0.5f,  -0.5f,   0.0f, 1.0f
		};

		const unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		mVertexArray = new VertexArray{ vertices, 4, indices, 6 };
	}
}