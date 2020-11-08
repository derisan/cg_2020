#pragma once

#include <vector>

#include <glm/glm.hpp>

class Actor
{
public:
	enum class State
	{
		kActive,
		kPaused,
		kDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update();
	virtual void UpdateActor() { };

	void ProcessInput(unsigned char key);
	virtual void ActorInput(unsigned char key) { };

	virtual void Draw(class Shader* shader) { };

	void ComputeWorldTransform();

	// Getters
	State GetState() const { return mState; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	glm::vec3 GetForward() const;
	glm::vec3 GetRight() const;

	// Setters
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void SetAxis(const glm::vec3& axis) { mAxis = axis; }

protected:
	class Game* mGame;
	const float dt{ 16.0f / 1000.0f };

private:
	State mState;

	// Transforms
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	float mScale;
	float mRotation;
	glm::vec3 mAxis;

	bool mRecomputeWorldTransform;
};
