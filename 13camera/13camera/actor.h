#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "gfw.h"

class Actor
{
public:
	enum class State
	{
		kActive,
		kPaused,
		kDead
	};

	Actor(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kDefault);
	virtual ~Actor();

	void Update();
	void UpdateComponents();
	virtual void UpdateActor() { };

	void ProcessInput(bool* keyState, int x, int y);
	virtual void ActorInput(bool* keyState, int x, int y) { };

	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	class Gfw* GetGfw() { return mGfw; }

	// Getters
	int GetLayer() const { return mLayer; }
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

protected:
	class Gfw* mGfw;

private:
	std::vector<class Component*> mComponents;

	Gfw::Layer mLayer;
	State mState;

	// Transforms
	glm::mat4 mWorldTransform;
	glm::vec3 mPosition;
	float mScale;
	float mRotation;

	bool mRecomputeWorldTransform;
};
