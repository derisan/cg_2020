// -----------------------------------
// 실습5. 화면에 삼각형 그리고 회전시키기
// 2016180007 김명규
// -----------------------------------

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "utils.h"
#include "Triangle.h"

void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);


// Screen width, height
const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

// Verts
const float vertices[] = {
	0.0f, 0.1f, 0.0f,
	0.1f, -0.1f, 0.0f,
	-0.1f, -0.1f, 0.0f
};

// Indices
const unsigned int indices[] = {
	2, 1, 0
};

// Shader
Shader* shader = nullptr;

// Vertex array
VertexArray* vao = nullptr;

// Triangles
std::vector<Triangle*> triangles;
unsigned int curIdx = 0;

// Some globals
bool shouldChangeColor = false;
bool shouldChangeMode = false;
bool shouldAnimPlay = false;

int main(int argc, char** argv)
{
	if (!window::init(SCR_WIDTH, SCR_HEIGHT, &argc, argv))
		exit(EXIT_FAILURE);

	Random::init();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	triangles.emplace_back(new Triangle(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	triangles.emplace_back(new Triangle(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	triangles.emplace_back(new Triangle(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	triangles.emplace_back(new Triangle(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)));

	shader = createShader("vert.glsl", "frag.glsl");
	vao = createVertexArray(vertices, 3, indices, 3);

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->use();
	vao->use();

	if (shouldChangeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Change triangles color
	if (shouldChangeColor)
	{
		shouldChangeColor = false;
		for (auto tri : triangles)
			tri->setColor(glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat()));
	}

	for (auto tri : triangles)
	{
		if (shouldAnimPlay)
			tri->move();

		glm::mat4 trans(glm::mat4(1.0f));
		trans = glm::translate(trans, tri->getWorld());
		shader->setMat4("world", trans);
		shader->setVec3("color", tri->getColor());
		tri->draw();
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
		case 'f': case 'F':
			shouldChangeMode = !shouldChangeMode;
			break;
		case 'm': case 'M':
			if (!shouldAnimPlay)
			{
				shouldAnimPlay = true;
				glutTimerFunc(16, timer, 1);
			}
			break;
		case 's': case 'S':
			shouldAnimPlay = false;
			break;
		case 'c': case 'C':
			shouldChangeColor = true;
			break;
		case 'q': case 'Q':
			for (auto tri : triangles)
				delete tri;
			triangles.clear();
			glutLeaveMainLoop();
			break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glm::vec2 pos = screenToNDC(x, y, SCR_WIDTH, SCR_HEIGHT);

		triangles[(curIdx++) % 4]->setWorld(glm::vec3(pos, 0.0f));
	}
}

void timer(int value)
{
	if (shouldAnimPlay)
	{
		glutTimerFunc(16, timer, 1);
		glutPostRedisplay();
	}
}