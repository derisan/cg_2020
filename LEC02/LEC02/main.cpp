// -----------------------------------
// Ω¶¿Ã¥ı
// 2016180007 ±Ë∏Ì±‘
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
	triangles.emplace_back(new Triangle(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

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
	
	for (auto tri : triangles)
	{
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
	case 'q': case 'Q':
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