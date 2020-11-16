#include "mesh_component.h"

#include <GL/glew.h>

#include "actor.h"
#include "renderer.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"

MeshComponent::MeshComponent(Actor* owner, const std::string& file)
	: Component{ owner },
	mMesh{ nullptr },
	mTexture{ nullptr },
	mVertexArray{ nullptr }
{
	mOwner->GetGfw()->AddMesh(this);

	mMesh = Renderer::Get()->GetMesh(file);
	mTexture = mMesh->GetTexture();
	mVertexArray = mMesh->GetVertexArray();
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGfw()->RemoveMesh(this);
}

void MeshComponent::Draw(Shader* shader)
{
	shader->SetMatrix4Uniform("uWorld", mOwner->GetWorldTransform());
	mTexture->SetActive();
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}