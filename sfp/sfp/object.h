#pragma once

#include <vector>

#include <glm/vec2.hpp>

class Object
{
public:
	struct Side
	{
		glm::vec2 p1;
		glm::vec2 p2;
	};

	enum class State
	{
		kActive,
		kPaused,
		kDead
	};

	enum class Type
	{
		kTriangle,
		kRect,
		kPentagon
	};

	Object(class ObjectManager* manager);
	virtual ~Object();

	virtual void Update();
	virtual void Draw() {};
	virtual void Load() {};

	virtual const std::vector<Side>& GetSides() const = 0;
	virtual const std::vector<glm::vec2>& GetPoints() const = 0;

	// Getters
	State GetState() const { return mState; }
	Type GetType() const { return mType; }
	float GetXSpeed() const { return mXSpeed; }
	float GetYSpeed() const { return mYSpeed; }
	float GetGravity() const { return mGravity; }
	bool GetShouldGravityWork() const { return mShouldGravityWork; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetType(Type type) { mType = type; }
	void SetXSpeed(float speed) { mXSpeed = speed; }
	void SetYSpeed(float speed) { mYSpeed = speed; }
	void SetGravity(float g) { mGravity = g; }
	void SetShouldGravityWork(bool value) { mShouldGravityWork = value; }

protected:
	class ObjectManager* mManager;

private:
	State mState;
	Type mType;

	float mXSpeed;
	float mYSpeed;
	float mGravity;

	bool mShouldGravityWork;
};

