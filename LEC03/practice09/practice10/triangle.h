#pragma once

#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle();
	virtual ~Triangle();

	void Update();
	void Draw(class Shader* shader);
	void Pull();
	
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

	class VertexArray* vao;

	// Program specific
	float x_;
	float y_;
};

