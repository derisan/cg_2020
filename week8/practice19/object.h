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
		kBlack,
		kWhite,
		kGray,
		kDarkGray,
		kBrown
	};

	Object(Color color = Color::kBlack);
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
	float GetRotation() const { return mYRotation; }
	const glm::vec3& GetColor() const { return mColor; }
	bool IsZRotate() const { return mIsRotateZ; }
	bool IsXRotate() const { return mIsRotateX; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec3& position) { mPosition = position; mRecomputeWorldTransform = true; }
	void SetScale(const glm::vec3& scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetYRotation(float rotation) { mYRotation = rotation; mRecomputeWorldTransform = true; }
	void SetXRotation(float rotation) { mXRotation = rotation; mRecomputeWorldTransform = true; }
	void SetZRotation(float rotation) { mZRotation = rotation; mRecomputeWorldTransform = true; }
	void SetXRotate(bool value) { mIsRotateX = value; }
	void SetZRotate(bool value) { mIsRotateZ = value; }
	
private:
	State mState;
	
	// Transform
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	glm::vec3 mScale;
	float mYRotation;

	glm::vec3 mColor;

	bool mRecomputeWorldTransform;

	// Program specific
	bool mIsRotateX;
	bool mIsRotateZ;
	float mXRotation;
	float mZRotation;
};

