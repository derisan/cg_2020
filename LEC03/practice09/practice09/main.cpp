// -----------------------------------
// 실습9. 화면에 삼각형 4개를 사용하여 사각형을 그리고 이동하기
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
	// pos					// color
	0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
	-0.25f, -0.25f, 0.0f,	0.0f, 1.0f, 0.0f,
	0.25f, -0.25f, 0.0f,	0.0f, 0.0f, 1.0f
};

const unsigned int indices[] = {
	0, 1, 2
};

// Shader
Shader* shader = nullptr;

// Vertex array
VertexArray* vao = nullptr;

// Triangles
std::vector<Triangle*> triangles;

// Some globals
bool should_move = false;
bool should_stretch = false;

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
	vao = CreateVertexArray(vertices, 3, indices, 3);

	LoadData();
	
	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->SetActive();
	vao->SetActive();

	for (auto tri : triangles)
	{
		if (should_move || should_stretch)
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
			if (!should_move)
			{
				should_move = true;
				for (auto tri : triangles)
					tri->SetMove(true);
			}
			break;
		case 'm': case 'M':
			if (!should_stretch)
			{
				should_stretch = true;
				for (auto tri : triangles)
					tri->SetStretch(true);
			}
			break;
		case 's': case 'S':
			should_move = false;
			should_stretch = false;
			for (auto tri : triangles)
			{
				tri->SetMove(false);
				tri->SetStretch(false);
			}
			break;
		case 'q': case 'Q':
			for (auto tri : triangles)
				delete tri;
			triangles.clear();
			glutLeaveMainLoop();
			break;
	}

	if (should_move || should_stretch)
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
	if (should_move || should_stretch)
	{
		glutTimerFunc(16, timer, 1);
		glutPostRedisplay();
	}
}

void LoadData()
{
	float angle = 0.0f;

	for (int i = 0; i < 4; ++i)
	{
		auto tri = new Triangle();
		tri->SetRotation(angle);
		triangles.emplace_back(tri);

		angle += 90.0f;
	}
}