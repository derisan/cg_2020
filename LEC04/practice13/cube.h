#pragma once

#include <glm/glm.hpp>

class Cube
{
public:
	enum class State
	{
		kActive,
		kPaused,
		kDead
	};

	Cube();
	~Cube();

	void Update(float dt);
	void Draw(class Shader* shader);

	void ComputeWorldTransform();
	void Load();

	// Getters
	State GetState() const { return mState; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	const glm::vec3& GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }


	// Setters
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	void SetScale(const glm::vec3& scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

private:
	State mState;

	// Transforms
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	glm::vec3 mScale;
	float mRotation;

	bool mRecomputeWorldTransform;

	class VertexArray* mVertexArray;

	// Program specific
	int mNum;
};

