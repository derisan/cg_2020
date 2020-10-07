// -----------------------------------
// 실습6. 원형 애니메이션
// 2016180007 김명규
// -----------------------------------

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "utils.h"
#include "Circle.h"
#include <cmath>
#include <algorithm>

// Callback functions
void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);


// Screen width, height
const int kScrWidth = 600;
const int kScrHeight = 600;

// Shader and VAO
Shader* shader = nullptr;
VertexArray* vao = nullptr;

// Some globals
bool shouldChangeMode = false;
GLenum drawMode = 0x0002;

// Circles
std::vector<Circle*> circles;

int main(int argc, char** argv)
{
	if (!window::init(kScrWidth, kScrHeight, &argc, argv))
		exit(EXIT_FAILURE);

	Random::init();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	shader = createShader("basic.vs", "basic.fs");

	// Set Animation
	glutTimerFunc(16, timer, 1);

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Change draw mode if 'f' key down
	if (shouldChangeMode)
	{
		drawMode = GL_POINTS;
		glPointSize(2.0f);
	}
	else
		drawMode = GL_LINE_LOOP;
	
	for (auto circle : circles)
	{
		circle->update();

		// circle dies when its radius bigger than 1 and if it's destined to die
		if (circle->getState() == Circle::State::kDead)
		{
			auto iter = std::find(circles.begin(), circles.end(), circle);
			if (iter != circles.end())
			{
				std::iter_swap(iter, circles.end() - 1);
				delete circle;
				circles.pop_back();
			}
		}
	}
	
	shader->use();
	for (auto circle : circles)
		circle->draw(drawMode);

	std::cout << "Current number of circle>> " << circles.size() << std::endl;
	
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'f': case 'F':
			shouldChangeMode = !shouldChangeMode;
			break;
		case 'c': case 'C':
			for (auto circle : circles)
				delete circle;
			circles.clear();
			break;
		case 'q': case 'Q':
			for (auto circle : circles)
				delete circle;
			circles.clear();
			delete vao;
			delete shader;
			glutLeaveMainLoop();
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glm::vec2 pos = screenToNDC(x, y, kScrWidth, kScrHeight);

		// Create circle if less than 10
		if (circles.size() < 10)
			circles.emplace_back(new Circle(pos, static_cast<Circle::Destiny>(Random::getInt())));
		else
			std::cout << "Failed to create circle. It's already 10." << '\n';
	}
}

void timer(int value)
{
	glutTimerFunc(16, timer, 1);
	glutPostRedisplay();
}