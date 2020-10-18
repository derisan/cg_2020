#include "earth.h"

#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "random.h"
#include "shader.h"
#include "vertexarray.h"

Earth::Earth()
	: Planet{},
	mSpeed{ Random::GetFloatRange(0.3f, 1.5f) },
	mAngle{ 0.0f },
	mRevAxis{ 0.0f, 1.0f, 0.0f },
	mPrevPosition{ GetPosition() }
{
	SetScale(0.1f);

	
}

void Earth::Update(float dt)
{
	Planet::Update(dt);

	if (GetState() == State::kActive)
	{
		mAngle += cos(dt) * mSpeed;
		
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
}

void Earth::OnUpdateWorldTransform()
{

}