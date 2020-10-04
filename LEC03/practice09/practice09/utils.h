#pragma once

#include <iostream>
#include <random>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
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
		std::uniform_real_distribution<float> dist(min, max);
		return dist(generator);
	}

	static int getInt(int min = 0, int max = 1)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(generator);
	}

private:
	static std::mt19937_64 generator;
};

std::mt19937_64 Random::generator;


namespace window
{
	bool init(int width, int height, int* argc = nullptr, char** argv = nullptr)
	{
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(width, height);
		glutCreateWindow("My Program");

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Unable to initialize GLEW" << std::endl;
			return false;
		}
		else
		{
			std::cout << "GLEW Initialization" << std::endl;
			return true;
		}
	}
}

glm::vec2 screenToNDC(int x, int y, float width = 600.0f, float height = 600.0f)
{
	float retX = ((float)x - width / 2) * (2 / width);
	float retY = ((float)-y + height / 2) * (2 / height);

	return glm::vec2(retX, retY);
}