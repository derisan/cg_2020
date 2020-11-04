#include "sphere.h"

#include <GL/glew.h>

#include <vector>

#include "vertexarray.h"
#include "shader.h"

Sphere::Sphere()
	: Object{},
	mVertexArray{ nullptr },
    mAngle{ 0.0f }
{
	Load();
}

Sphere::~Sphere()
{
	delete mVertexArray;
}

void Sphere::Update()
{
    if (GetState() == State::kActive)
    {
        Object::Update();

        if (GetIsPlanet())
        {
            mAngle += cos(dt);
            SetRotation(mAngle);
        }
    }
}

void Sphere::Draw(Shader* shader)
{
	Object::Draw(shader);

	mVertexArray->SetActive();
    glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Sphere::Load()
{
    std::vector<float> vertices;
    vertices.reserve(10368);
   
    float radius{ 1.0f };
    const float PI{ 3.141592f };
    const unsigned int sectorCount{ 72 };
    const unsigned int stackCount{ 24 };
    
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }

    std::vector<unsigned int> indices;
    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    mVertexArray = new VertexArray{ vertices.data(), static_cast<unsigned int>(vertices.size() / 6), 
        indices.data(), static_cast<unsigned int>(indices.size()) };
}