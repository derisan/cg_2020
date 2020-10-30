#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "object.h"

class ObjectManager
{
public:
	ObjectManager(class Game* game);
	~ObjectManager();

	void Update();
	void Draw();
	
	void AddObj(class Object* obj);
	void RemoveObj(class Object* obj);
	
	void GenerateRandomPolygon();
	void CreatePath(const glm::vec2& p1, const glm::vec2& p2);

	void CheckCollision(class Line* cutter);
	void CheckSide(const glm::vec2& p1, const glm::vec2& p2,
		const Object::Side& s1, const Object::Side& s2, class Object* obj);
	int GetTriangleDivideOption(const Object::Side& s1, const Object::Side& s2, class Object* obj);
	int GetRectDivideOption(const Object::Side& s1, const Object::Side& s2, class Object* obj);
	void DivideTriangleIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, class Object* obj);
	void DivideRectIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, class Object* obj);

	// Getters
	bool GetShouldDrawPath() const { return mShouldDrawPath; }

	// Setters
	void SetShouldDrawPath(bool value) { mShouldDrawPath = value; }

private:
	std::vector<class Object*> mObjs;
	std::vector<class Line*> mPaths;

	float mCooldown;
	
	const float dt{ 16.0f / 1000.0f };

	bool mShouldDrawPath;

	class Game* mGame;
};

