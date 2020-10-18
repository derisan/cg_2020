#include "moon.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Moon::Moon()
	: Planet{},
	mSpeed{ 0.0f },
	mAngle{ 0.0f },
	mRevAxis{ 0.0f }
{
	SetScale(0.03f);
}

void Moon::Update(float dt)
{
	Planet::Update(dt);

	if (GetState() == State::kActive)
		mAngle += cos(dt) * mSpeed;
}

void Moon::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorld", GetWorldTransform());

	glm::mat4 rev{ 1.0f };
	rev = glm::rotate(rev, glm::radians(mAngle), mRevAxis);
	shader->SetMatrixUniform("uRev", rev);

	GetVertexArray()->SetActive();
	glDrawElements(GL_TRIANGLES, GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}