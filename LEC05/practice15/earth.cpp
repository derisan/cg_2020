#include "earth.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "random.h"
#include "shader.h"
#include "vertexarray.h"
#include "moon.h"

Earth::Earth()
	: Planet{},
	mSpeed{ Random::GetFloatRange(0.3f, 1.5f) },
	mAngle{ 0.0f },
	mRevAxis{ 0.0f, 1.0f, 0.0f },
	mPrevPosition{ GetPosition() },
	mMoon{ nullptr }
{
	SetScale(0.1f);

	mMoon = new Moon{ this };
	mMoon->SetState(State::kActive);
}

void Earth::Update(float dt)
{
	Planet::Update(dt);

	if (GetState() == State::kActive)
	{
		mAngle += cos(dt) * mSpeed;
		mMoon->Update(dt);
	}
}

void Earth::Draw(Shader* shader)
{
	glm::mat4 rev{ 1.0f };
	rev = glm::rotate(rev, glm::radians(mAngle), mRevAxis);
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	shader->SetMatrixUniform("uRev", rev);

	GetVertexArray()->SetActive();
	glDrawElements(GL_TRIANGLES, GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

	mMoon->Draw(shader);
}

void Earth::OnUpdateWorldTransform()
{

}