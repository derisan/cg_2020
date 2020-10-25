#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>

#include "random.h"

// Init freeglut and create window
bool Init(int w, int h, int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(w, h);
	glutCreateWindow("Practice 15");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		return false;
	}
	else
	{
		std::cout << "GLEW Initialization" << std::endl;
		return true;
	}
}

glm::vec2 ScreenToNDC(int x, int y, float w, float h)
{
	float retX = (static_cast<float>(x) - w / 2) * (2 / w);
	float retY = (static_cast<float>(-y) + h / 2) * (2 / h);

	return glm::vec2{ retX, retY };
}
