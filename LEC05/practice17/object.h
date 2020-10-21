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

	Object();
	virtual ~Object() = default;

	virtual void Update(float dt);
	virtual void Draw(class Shader* shader) { };
	virtual void Load() { };

	// Getters
	State GetState() const { return mState; }
	float GetAngle() const { return mAngle; }
	const glm::mat4& GetWorldTransform() { return mWorldTransform; }

	// Setters
	void SetState(State state) { mState = state; }
	void SetWorldTransform(const glm::mat4& world) { mWorldTransform = world; }

	void SetWorldRotate(float angle, const glm::vec3& vec)
	{
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(angle), vec);
	}

	void SetWorldTranslate(const glm::vec3& vec)
	{
		mWorldTransform = glm::translate(mWorldTransform, vec);
	}

	void SetWorldScale(const glm::vec3& vec)
	{
		mWorldTransform = glm::scale(mWorldTransform, vec);
	}
private:
	State mState;
	glm::mat4 mWorldTransform;
	float mAngle;
};

