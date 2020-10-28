#include "sphere.h"

#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Sphere::Sphere(Color color)
	: Object{ color },
	mVertexArray{ nullptr }
{
	Load();
}

Sphere::~Sphere()
{
	delete mVertexArray;
}

void Sphere::Update(float dt)
{
	Object::Update(dt);
}

void Sphere::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Sphere::Load()
{
	const float PI = acosf(-1);
	const float radius = 0.5f;
	const int sectorCount = 20;
	const int stackCount = 10;
	

	float x, y, z, xy;                              // vertex position

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	std::vector<float> vertices;
	vertices.reserve(1200);

	std::vector<unsigned int> indices;
	indices.reserve(600);

	glm::vec3 color = GetColor();

	for (unsigned int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (unsigned int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);

		}
	}

	// indices
	//  k1--k1+1
	//  |  / |
	//  | /  |
	//  k2--k2+1
	unsigned int k1, k2;
	for (unsigned int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding 1st and last stacks
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	mVertexArray = new VertexArray(vertices.data(), vertices.size() / 6, indices.data(), indices.size());
}

