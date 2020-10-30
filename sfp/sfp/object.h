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

	Object(class ObjectManager* manager);
	virtual ~Object();

	virtual void Update();
	virtual void Draw() {};
	virtual void Load() {};

	virtual const std::vector<Side>& GetSides() const = 0;
	virtual const std::vector<glm::vec2>& GetPoints() const = 0;

	// Getters
	State GetState() const { return mState; }
	float GetXSpeed() const { return mXSpeed; }
	float GetYSpeed() const { return mYSpeed; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetXSpeed(float speed) { mXSpeed = speed; }
	void SetYSpeed(float speed) { mYSpeed = speed; }

protected:
	class ObjectManager* mManager;

private:
	State mState;

	float mXSpeed;
	float mYSpeed;
};

