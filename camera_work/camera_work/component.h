#pragma once

class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();

	virtual void Update() {};
	virtual void ProcessKeyboardInput(bool* keyState) { };
	virtual void OnUpdateWorldTransform() { };

protected:
	class Actor* mOwner;
};