#include "moonOrbit.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vertexarray.h"

MoonOrbit::MoonOrbit()
	: Orbit{},
	mAngle{ 0.0f },
	mSpeed{ 0.0f },
	mRevAxis{ 0.0f }
{
	SetScale(0.15f);
}

void MoonOrbit::Update(float dt)
{
	Orbit::Update(dt);

	if (GetState() == State::kActive)
		mAngle += cos(dt) * mSpeed;
}

void MoonOrbit::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorld", GetWorldTransform());

	glm::mat4 rev{ 1.0f };
	rev = glm::rotate(rev, glm::radians(mAngle), mRevAxis);
	shader->SetMatrixUniform("uRev", rev);

	GetVertexArray()->SetActive();
	glDrawArrays(GL_LINE_STRIP, 0, 360);
}