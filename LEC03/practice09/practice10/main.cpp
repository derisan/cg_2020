// -----------------------------------
// 실습10. 여러 도형 그리기
// 2016180007 김명규
// -----------------------------------

#include <vector>

#include "shader.h"
#include "vertexarray.h"
#include "utils.h"
#include "triangle.h"
#include "rect.h"
#include "pentagon.h"
#include "dot.h"

// Callback funcs
void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);

void LoadData();

// Screen width, height
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// Shader
Shader* shader = nullptr;

// Figures
Triangle* triangle = nullptr;
Rect* rect = nullptr;
Pentagon* penta = nullptr;
Dot* dot = nullptr;

// Some globals
bool should_play = false;

int main(int argc, char** argv)
{
	if (!window::init(SCR_WIDTH, SCR_HEIGHT, &argc, argv))
		exit(EXIT_FAILURE);

	Random::init();

	// Bind callback funcs
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	// Create shader and va
	shader = CreateShader("Shaders/vert.glsl", "Shaders/frag.glsl");
	if (!shader)
		exit(EXIT_FAILURE);
	
	LoadData();
	
	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->SetActive();
	
	// for debug
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if (should_play)
	{
		triangle->Update();
		rect->Update();
		penta->Update();
		dot->Update();
	}

	triangle->Draw(shader);
	rect->Draw(shader);
	penta->Draw(shader);
	dot->Draw(shader);
	
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
		case 't': case 'T':
			if (!should_play)
				should_play = true;
			break;
		case 's': case 'S':
			should_play = false;
			break;
		case 'q': case 'Q':
			delete triangle;
			delete rect;
			delete penta;
			delete dot;
			glutLeaveMainLoop();
			break;
	}

	if (should_play)
		glutTimerFunc(16, timer, 1);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void timer(int value)
{
	if (should_play)
	{
		glutTimerFunc(16, timer, 1);
		glutPostRedisplay();
	}
}

void LoadData()
{
	triangle = new Triangle();
	triangle->SetColor(glm::vec3{ 0.0f, 0.5f, 1.0f });
	triangle->SetPosition(glm::vec2{ -0.5f, 0.5f });
	
	rect = new Rect();
	rect->SetColor(glm::vec3{ 1.0f, 1.0f, 0.0f });
	rect->SetPosition(glm::vec2{ 0.5f, 0.5f });

	penta = new Pentagon();
	penta->SetColor(glm::vec3{ 0.0f, 1.0f, 0.5f });
	penta->SetPosition(glm::vec2{ -0.5f, -0.5f });

	dot = new Dot();
	dot->SetColor(glm::vec3{ 1.0f, 0.0f, 0.0f });
	dot->SetPosition(glm::vec2{ 0.5f, -0.5f });
}