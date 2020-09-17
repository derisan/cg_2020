#pragma once

#include <random>
#include <glm/glm.hpp>

class Random
{
public:
	static void init()
	{
		std::random_device rd;
		generator.seed(rd());
	}

	// returns 0.0 ~ 1.0
	static float getFloat(float min = 0.0f, float max = 1.0f)
	{
		std::uniform_real_distribution<float> urd(min, max);
		return urd(generator);
	}

private:
	static std::mt19937_64 generator;
};

std::mt19937_64 Random::generator;


glm::vec2 screenToNDC(int x, int y, float width = 600.0f, float height = 600.0f)
{
	float retX = ((float)x - width / 2) * (2 / width);
	float retY = ((float)-y + height / 2) * (2 / height);

	return glm::vec2(retX, retY);
}
