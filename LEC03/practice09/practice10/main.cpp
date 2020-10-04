// -----------------------------------
// 실습10. 여러 도형 그리기
// 2016180007 김명규
// -----------------------------------

#include <vector>

#include "shader.h"
#include "vertexarray.h"
#include "utils.h"
#include "triangle.h"

void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);

void LoadData();

// Screen width, height
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// Verts and indices 
const float vertices[] = {
	// pos			
	0.0f, 0.0f, 0.0f,		
	-0.25f, -0.25f, 0.0f,	
	0.25f, -0.25f, 0.0f
};

const unsigned int indices[] = {
	0, 1, 2
};

// Shader
Shader* shader = nullptr;

// Triangles
std::vector<Triangle*> triangles;

// Some globals
bool should_play = false;


int main(int argc, char** argv)
{
	if (!window::init(SCR_WIDTH, SCR_HEIGHT, &argc, argv))
		exit(EXIT_FAILURE);

	Random::init();

	// Bind several funcs
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
	
	for (auto tri : triangles)
	{
		if (should_play)
			tri->Update();

		tri->Draw(shader);
	}

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
			for (auto tri : triangles)
				delete tri;
			triangles.clear();
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
	auto tri = new Triangle();
	tri->SetColor(glm::vec3{ 0.0f, 0.5f, 1.0f });
	tri->SetPosition(glm::vec2{ -0.5f, 0.5f });
	triangles.emplace_back(tri);
}