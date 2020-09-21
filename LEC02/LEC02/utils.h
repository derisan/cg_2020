#pragma once

#include <random>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

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

