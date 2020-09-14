#pragma once

#include <random>


class Random
{
public:
	static void init()
	{
		std::random_device rd;
		generator.seed(rd());
	}

	// returns 0.0 ~ 1.0
	static float getFloat()
	{
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(generator);
	}

private:
	static std::mt19937_64 generator;
};

std::mt19937_64 Random::generator;


