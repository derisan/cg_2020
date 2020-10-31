#pragma once

#include "object.h"

class Triangle 
	: public Object
{
public:
	enum PointIdx
	{
		kLeft,
		kRight,
		kMid
	};

	Triangle(const glm::vec2& left, const glm::vec2& right, 
		const glm::vec2& mid, class ObjectManager* manager, 
		const glm::vec2& pathStart = glm::vec2{ 0.0f, 0.0f }, const glm::vec2& pathEnd = glm::vec2{ 0.0f, 0.0f });
	~Triangle();

	void Update() override;
	void UpdateSide();
	void Draw() override;
	void Load() override;
	const glm::vec2 GetCenter() const override;
	void Rearrange(const glm::vec2& center) override;

	const std::vector<Side>& GetSides() const override { return mSides; }
	const std::vector<glm::vec2>& GetPoints() const override { return mPoints; }

private:
	glm::vec2 mLeftPoint;
	glm::vec2 mRightPoint;
	glm::vec2 mMidPoint;
	
	std::vector<Side> mSides;
	std::vector<glm::vec2> mPoints;

	class Line* mPath;
	class VertexArray* mVertexArray;
};

