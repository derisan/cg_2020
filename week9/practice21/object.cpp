#include "object.h"

#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

Object::Object()
	: mState{ State::kActive },
	mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mRotation{ 0.0f },
	mColor{ 1.0f },
	mRecomputeWorldTransform{ true }
{

}

void Object::Update()
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();
}

void Object::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrix4Uniform("uWorld", mWorldTransform);
	shader->SetVectorUniform("objectColor", mColor);
}

void Object::ComputeWorldTransform()
{
	mRecomputeWorldTransform = false;

	mWorldTransform = glm::mat4{ 1.0f };
	mWorldTransform = glm::translate(mWorldTransform, mPosition);
	mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
	mWorldTransform = glm::scale(mWorldTransform, mScale);
}