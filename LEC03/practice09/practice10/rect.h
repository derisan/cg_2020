#pragma once

#include <glm/glm.hpp>

class Rect
{
public:
	Rect();
	virtual ~Rect();

	void Update(const glm::vec2& pos);
	void Draw(class Shader* shader);
	void UpdateVAO();
	void NearVertex(const glm::vec2& pos);

	// Getters
	const glm::vec2& GetPosition() const { return position_; }
	const glm::vec2& GetScale() const { return scale_; }
	float GetRotation() const { return rotation_; }
	const glm::vec3& GetColor() const { return color_; }
	float GetSpeed() const { return speed_; }

	// Setters
	void SetPosition(const glm::vec2& position) { position_ = position; }
	void SetScale(const glm::vec2& scale) { scale_ = scale; }
	void SetRotation(float rotation) { rotation_ = rotation; }
	void SetColor(const glm::vec3& color) { color_ = color; }
	void SetSpeed(float speed) { speed_ = speed; }
	
private:
	// Transform
	glm::vec2 position_;
	glm::vec2 scale_;
	float rotation_;

	glm::vec3 color_;
	float speed_;

	class VertexArray* vao_;

	// Program specific
	glm::vec2 lefttop_;
	glm::vec2 righttop_;
	glm::vec2 leftbot_;
	glm::vec2 rightbot_;
};

