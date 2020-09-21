// -----------------------------------
// Ω¶¿Ã¥ı
// 2016180007 ±Ë∏Ì±‘
// -----------------------------------

#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "utils.h"

void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);


// Screen width, height
const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;


// Verts
const float vertices[] = {
	0.0f, 0.25f, 0.0f,
	0.25f, -0.25f, 0.0f,
	-0.25f, -0.25f, 0.0f
};

// Indices
const unsigned int indices[] = {
	2, 1, 0
};

// Shader
Shader* shader = nullptr;

// Vertex array
VertexArray* vao = nullptr;

int main(int argc, char** argv)
{
	if (!window::init(SCR_WIDTH, SCR_HEIGHT, &argc, argv))
		exit(EXIT_FAILURE);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

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
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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

