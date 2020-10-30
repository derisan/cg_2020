#pragma once

#include "object.h"

class Triangle 
	: public Object
{
public:
	Triangle(const glm::vec2& left, const glm::vec2& right, 
		const glm::vec2& mid, class ObjectManager* manager);
	~Triangle();

	void Update() override;
	void Draw() override;
	void Load() override;

	// Class specific
	void UpdateSide();

	const glm::vec2& GetLeftPoint() const { return mLeftPoint; }
	const glm::vec2& GetRightPoint() const { return mRightPoint; }
	const glm::vec2& GetMidPoint() const { return mMidPoint; }
	const std::vector<Side>& GetSides() const override { return mSides; } 

private:
	glm::vec2 mLeftPoint;
	glm::vec2 mRightPoint;
	glm::vec2 mMidPoint;

	Side mLeftSide;
	Side mRightSide;
	Side mMidSide;
	
	std::vector<Side> mSides;

	class VertexArray* mVertexArray;
};

