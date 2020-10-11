// -----------------------------------
// 실습12. 꼭지점을 이용하여 3차원 객체 그리기
// 2016180007 김명규
// -----------------------------------

#include "utils.h"
#include "random.h"

// Callback functions
void Draw();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);

void LoadData();

const int kScrWidth{ 800 };
const int kScrHeight{ 600 };

int main(int argc, char** argv)
{
	bool success = Init(kScrWidth, kScrHeight, &argc, argv);
	if (!success)
		exit(EXIT_FAILURE);
	Random::Init();

	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
	return 0;
}

void Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// Update

	// Draw


	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q': case 'Q':
			glutLeaveMainLoop();
			break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}

void Timer(int value)
{

}

void LoadData()
{

}