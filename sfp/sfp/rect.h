#pragma once
#include "object.h"
class Rect :
    public Object
{
public:
	enum PointIdx
	{
		kLeftTopPoint,
		kRightTopPoint,
		kLeftBottomPoint,
		kRightBottomPoint
	};

	enum SideIdx
	{
		kTopSide,
		kRightSide,
		kBottomSide,
		kLeftSide
	};

	Rect(const glm::vec2& leftTop, const glm::vec2& rightTop,
		const glm::vec2& leftBottom, const glm::vec2& rightBottom, class ObjectManager* manager);
	~Rect();

	void Update() override;
	void Draw() override;
	void Load() override;

	// Class specific
	void UpdateSide();

	const std::vector<Side>& GetSides() const override { return mSides; }
	const std::vector<glm::vec2>& GetPoints() const override { return mPoints; }
private:
	glm::vec2 mLeftTopPoint;
	glm::vec2 mRightTopPoint;
	glm::vec2 mLeftBottomPoint;
	glm::vec2 mRightBottomPoint;

	std::vector<Side> mSides;
	std::vector<glm::vec2> mPoints;

	class VertexArray* mVertexArray;
};

