#pragma once

#include <random>

class Random
{
public:
	static void init();
	static int getInt(int min, int max);
private:
	static std::mt19937 generator;
};

void Random::init()
{
	std::random_device rd;
	generator.seed(rd());
}

int Random::getInt(int min, int max)
{
	std::uniform_int_distribution<int> uid(min, max);
	return uid(generator);
}

std::mt19937 Random::generator;