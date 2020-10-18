#include "moon.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "random.h"
#include "shader.h"
#include "earth.h"
#include "vertexarray.h"

Moon::Moon(Earth* owner)
	: Planet{},
	mAngle{ 0.0f },
	mSpeed{ Random::GetFloatRange(0.3f, 1.0f) },
	mOwner{ owner }
{
	SetScale(0.05f);
}

void Moon::Update(float dt)
{
	Planet::Update(dt);

	if (GetState() == State::kActive)
	{
		mAngle += cos(dt) * mSpeed;
	}
}

void Moon::Draw(Shader* shader)
{
	glm::mat4 rev{ 1.0f };
	rev = glm::rotate(rev, glm::radians(mAngle), mOwner->GetRevAxis());
	rev = glm::rotate(rev, glm::radians(mAngle), mOwner->GetPosition());
	rev = glm::translate(rev, mOwner->GetPosition());
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	shader->SetMatrixUniform("uRev", rev);

	GetVertexArray()->SetActive();
	glDrawElements(GL_TRIANGLES, GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

