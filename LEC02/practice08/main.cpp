// -----------------------------------
// ½Ç½À8. »ï°¢Çü Æ¨±â±â
// 2016180007 ±è¸í±Ô
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

void createTriangles(float x, float y, float scale = 1.0f, float border = 0.9f);


// Screen width, height
const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

// Verts and indices for triangles
const float vertices[] = {
	0.0f, 0.2f, 0.0f,
	0.1f, -0.1f, 0.0f,
	-0.1f, -0.1f, 0.0f
};

const unsigned int indices[] = {
	2, 1, 0
};

// Verts and indices for rect
const float verticesRect[] = {
	0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f	// top left
};

const unsigned int indicesRect[] = {
	0, 1, 3,
	1, 2, 3
};

// Shader
Shader* shader = nullptr;

// Vertex array
VertexArray* vao = nullptr;
VertexArray* vaoRect = nullptr;

// Triangles
std::vector<Triangle*> triangles;

// Some globals
bool shouldChangeMode = false;
bool shouldAnimPlay = false;

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


	// Create 1 big triangle and 2 small triangles
	createTriangles(-0.9f, 0.0f, 1.0f);
	createTriangles(Random::getFloat(-0.5f, 0.5f), -0.45f, 0.5f, 0.45f);
	createTriangles(Random::getFloat(-0.5f, 0.5f), 0.45f, 0.5f, 0.45f);
	triangles[1]->setRotation(0.0f);
	triangles[2]->setRotation(-180.0f);


	// Create shader and va
	shader = createShader("vert.glsl", "frag.glsl");
	vao = createVertexArray(vertices, 3, indices, 3);
	vaoRect = createVertexArray(verticesRect, 4, indicesRect, 6);

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	vaoRect->use();
	shader->use();
	shader->setMat4("world", glm::mat4(1.0f));
	shader->setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shader->use();
	vao->use();

	if (shouldChangeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (auto tri : triangles)
	{
		if (shouldAnimPlay)
			tri->move();
			
		if (tri->getChangeColor())
		{
			tri->setChangeColor(false);
			tri->setColor(glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat()));
		}

		glm::mat4 trans(glm::mat4(1.0f));
		trans = glm::translate(trans, tri->getWorld());
		trans = glm::rotate(trans, glm::radians(tri->getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, tri->getScale());
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
		case 'r': case 'R':
			for (auto tri : triangles)
				delete tri;
			triangles.clear();
		case 'p': case 'P':
			if (!triangles.empty())
			{
				delete triangles.back();
				triangles.pop_back();
			}
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

		if (triangles.size() < 10)
			createTriangles(pos.x, pos.y);
		else
			std::cout << "Failed to create triangle. It's alredy 10." << '\n';
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

void createTriangles(float x, float y, float scale, float border)
{
	triangles.emplace_back(new Triangle(glm::vec3(x, y, 0.0f),
		glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat()), glm::vec3(scale, scale, 0.0f), border));
}