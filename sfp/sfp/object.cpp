#include "object.h"

#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

Object::Object()
	: mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mColor{ 0.38f, 0.2f, 0.07f },
	mRecomputeWorldTransform{ true }
{

}

void Object::Update(float dt)
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();
}

void Object::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetVectorUniform("uColor", GetColor());
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
}

void Object::ComputeWorldTransform()
{
	mRecomputeWorldTransform = false;

	mWorldTransform = glm::mat4{ 1.0f };
	mWorldTransform = glm::translate(mWorldTransform, mPosition);
	mWorldTransform = glm::scale(mWorldTransform, mScale);
}
