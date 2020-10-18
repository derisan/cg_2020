#pragma once

#include <glm/glm.hpp>

class Sun
{
public:
	Sun();

	void Update(float dt);
	void Draw(class Shader* shader);
	void ComputeWorldTransform();

	void Load();
	
	// Getters
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	
	// Setters
	void SetPosition(const glm::vec3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	
private:
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	float mScale;
	float mRotation;

	bool mRecomputeWorldTransform;

	class VertexArray* mVertexArray;
};

