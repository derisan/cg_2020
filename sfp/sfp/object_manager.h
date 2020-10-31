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
	
	// Create triangle in left or right side of the window
	void GenerateRandomPolygon();

	// Create path when two points are given
	void CreatePath(const glm::vec2& p1, const glm::vec2& p2);

	// Check if the cutter collides with two sides of the single obj
	// Note:: this function checks triangle' side in order of left->right->mid
	// In case of rect, top->right->bottom->left side
	void CheckCollision(class Line* cutter);


	void CheckSide(const glm::vec2& p1, const glm::vec2& p2,
		const Object::Side& s1, const Object::Side& s2, class Object* obj);

	// Return divide option along two sides whick collides with the cutter
	int GetTriangleDivideOption(const Object::Side& s1, const Object::Side& s2, class Object* obj);
	int GetRectDivideOption(const Object::Side& s1, const Object::Side& s2, class Object* obj);

	// Divide given triangle into one tri, one rect
	void DivideTriangleIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, class Object* obj);

	// Dive given rect into one tri, one penta or two rects
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

