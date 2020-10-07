// -----------------------------------
// 실습10. 여러 도형 그리기
// 2016180007 김명규
// -----------------------------------

#include <vector>
#include <iostream>

#include "shader.h"
#include "vertexarray.h"
#include "utils.h"
#include "rect.h"


// Callback funcs
void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);
void motion(int x, int y);

void LoadData();

// Screen width, height
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// Shader
Shader* shader = nullptr;

// Figures
Rect* rect = nullptr;

// Some globals
bool should_play = true;
bool is_left_down = false;
glm::vec2 mouse_pos = glm::vec2{ 0.0f, 0.0f };

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
	glutMotionFunc(motion);

	// Create shader and va
	shader = CreateShader("Shaders/vert.glsl", "Shaders/frag.glsl");
	if (!shader)
		exit(EXIT_FAILURE);
	
	LoadData();

	glutTimerFunc(16, timer, 1);
	
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
	
	if (is_left_down)
	{
		rect->Update(mouse_pos);
	}

	rect->Draw(shader);

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
			
			delete rect;
			
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
		is_left_down = true;
		mouse_pos = screenToNDC(x, y, SCR_WIDTH, SCR_HEIGHT);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		is_left_down = false;
}

void timer(int value)
{
	if (should_play)
	{
		glutTimerFunc(16, timer, 1);
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{
	if (is_left_down)
	{
		mouse_pos = screenToNDC(x, y, SCR_WIDTH, SCR_HEIGHT);

		std::cout << mouse_pos.x << ' ' << mouse_pos.y << std::endl;
	}
}

void LoadData()
{
	rect = new Rect();
	rect->SetColor(glm::vec3{ 1.0f, 1.0f, 0.0f });
	rect->SetPosition(glm::vec2{ 0.0f, 0.0f });

}