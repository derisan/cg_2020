#pragma once

#include <glm/vec2.hpp>

class Line
{
public:
	Line(const glm::vec2& start, const glm::vec2& end);
	~Line();

	void Draw();
	void Load();

	const glm::vec2& GetStart() const { return mStart; }
	const glm::vec2& GetEnd() const { return mEnd; }

private:
	glm::vec2 mStart;
	glm::vec2 mEnd;

	class VertexArray* mVertexArray;
};

