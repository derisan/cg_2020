#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object
{
public:
	enum class State
	{
		kActive,
		kPaused
	};

	enum Color
	{
		kRed,
		kGreen,
		kBlue,
		kYellow,
		kMagenta,
		kCyan,
		kBlack
	};

	Object(Color color = Color::kBlack, bool rotateX = false);
	virtual ~Object() = default;

	virtual void Update(float dt);
	virtual void Draw(class Shader* shader) { };
	virtual void Load() { };

	void ComputeWorldTransform();

	// Getters
	State GetState() const { return mState; }
	const glm::mat4& GetWorldTransform() { return mWorldTransform; }
	const glm::vec3& GetPosition() const { return mPosition; }
	const glm::vec3& GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const glm::vec3& GetColor() const { return mColor; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	void SetScale(const glm::vec3& scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	void SetXRotation(float rotation) { mXRotation = rotation; mRecomputeWorldTransform = true; }
	

private:
	State mState;
	
	// Transform
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	glm::vec3 mScale;
	float mRotation;

	glm::vec3 mColor;

	bool mRecomputeWorldTransform;

	// Program specific
	bool mIsRotateX;
	float mXRotation;
};

