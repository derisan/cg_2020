#include "main_scene.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gfw.h"
#include "renderer.h"
#include "shader.h"
#include "actor.h"
#include "mesh_component.h"

MainScene::MainScene(Gfw* gfw)
	: Scene{ gfw },
	mMeshShader{ nullptr }
{
	mMeshShader = Renderer::Get()->GetShader("mesh");

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mGfw->GetScrWidth()) / mGfw->GetScrHeight(),
		0.1f, 100.0f);
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(glm::vec3{ 0.0f, 1.0f, 3.0f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
	mMeshShader->SetActive();
	mMeshShader->SetMatrix4Uniform("uView", view);
	mMeshShader->SetMatrix4Uniform("uProj", proj);
}


void MainScene::Enter()
{
	auto chr = new Actor{ mGfw };
	auto mc = new MeshComponent{ chr, "Assets/bunny.gpmesh" };
}

void MainScene::Exit()
{
	mGfw->RemoveAllActors();
}

void MainScene::ProcessInput(unsigned char key)
{

}

void MainScene::Update()
{

}

void MainScene::Draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	mMeshShader->SetActive();
	for (auto mesh : mGfw->GetMeshes())
		mesh->Draw(mMeshShader);

	glutSwapBuffers();
}