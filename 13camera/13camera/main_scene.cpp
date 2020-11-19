#include "main_scene.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gfw.h"
#include "renderer.h"
#include "shader.h"
#include "fps_actor.h"
#include "follow_actor.h"
#include "robot.h"
#include "mesh_component.h"

MainScene::MainScene(Gfw* gfw)
	: Scene{ gfw },
	mMeshShader{ nullptr },
	mFps{ nullptr },
	mFollow{ nullptr }
{
	mMeshShader = Renderer::Get()->GetShader("mesh");

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mGfw->GetScrWidth()) / mGfw->GetScrHeight(),
		0.1f, 100.0f);
	mMeshShader->SetActive();
	mMeshShader->SetMatrix4Uniform("uProj", proj);
}


void MainScene::Enter()
{
	mFps = new FpsActor{ mGfw };
	mFollow = new FollowActor{ mGfw };
	new Robot{ mGfw };

	for (int i = 0; i < 10; ++i)
	{
		auto plane = new Actor{ mGfw };
		plane->SetPosition(glm::vec3{ 0.0f, -1.0f, -2.0f * i });
		auto mc = new MeshComponent{ plane, "Assets/road.gpmesh" };
	}
}

void MainScene::Exit()
{
	mGfw->RemoveAllActors();
}

void MainScene::ProcessInput(bool* keyState, int x, int y)
{

}

void MainScene::Update()
{

}

void MainScene::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	mMeshShader->SetActive();
	//mMeshShader->SetMatrix4Uniform("uView", mFps->GetView());
	mMeshShader->SetMatrix4Uniform("uView", mFollow->GetView());
	for (auto mesh : mGfw->GetMeshes())
		mesh->Draw(mMeshShader);

	glutSwapBuffers();
}