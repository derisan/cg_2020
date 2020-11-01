#pragma once

#include <glm/glm.hpp>

class Object
{
public:
	enum class State
	{
		kActive,
		kPaused,
		kDead
	};

	Object();
	virtual ~Object() = default;

	virtual void Update();
	virtual void Draw(class Shader* shader);
	virtual void Load() = 0;

	
	// Getters
	State GetState() const { return mState; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const glm::vec3& GetColor() const { return mColor; }

	
	// Setters
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void SetColor(const glm::vec3& color) { mColor = color; }
	

private:
	void ComputeWorldTransform();

	State mState;

	// Transforms
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	float mScale;
	float mRotation;
	
	glm::vec3 mColor;

	bool mRecomputeWorldTransform;
};

