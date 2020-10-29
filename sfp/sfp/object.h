#pragma once

#include <glm/glm.hpp>

class Object
{
public:
	Object();
	virtual ~Object() = default;

	virtual void Update(float dt);
	virtual void Draw(class Shader* shader);
	virtual void Load() { };

	void ComputeWorldTransform();

	// Getters
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	const glm::vec3& GetScale() const { return mScale; }
	const glm::vec3& GetColor() const { return mColor; }

	// Setters
	void SetPosition(const glm::vec3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	void SetScale(const glm::vec3& scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetColor(const glm::vec3& color) { mColor = color; }

private:
	// Transform
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	glm::vec3 mScale;

	// Color
	glm::vec3 mColor;

	bool mRecomputeWorldTransform;
};

