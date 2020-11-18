#pragma once

class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();

	virtual void Update() {};
	virtual void ProcessInput(bool* keyState, int x, int y) { };
	virtual void OnUpdateWorldTransform() { };

protected:
	class Actor* mOwner;
};