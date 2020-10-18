#pragma once

#include <glm/glm.hpp>

class Object
{
public:
	enum class State
	{
		kActive,
		kPaused
	};

	Object();
	virtual ~Object() = default;

	virtual void Update(float dt);
	virtual void Draw(class Shader* shader) {};
	virtual void Load() {};
	void ComputeWorldTransform();
	virtual void OnUpdateWorldTransform() {};

	// Getters
	State GetState() const { return mState; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const glm::vec3& GetAxis() const { return mAxis; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetWorldTransform(const glm::mat4& world) { mWorldTransform = world;}
	void SetPosition(const glm::vec3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void SetAxis(const glm::vec3& axis) { mAxis = axis; mRecomputeWorldTransform = true; }

private:
	State mState;

	// Transform
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	float mScale;
	float mRotation;
	glm::vec3 mAxis;

	bool mRecomputeWorldTransform;
};

