#include "cylinder.h"

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Cylinder::Cylinder(Color color)
	: Object{ color },
	mVertexArray{ nullptr }
{
	Load();
}

Cylinder::~Cylinder()
{
	delete mVertexArray;
}

void Cylinder::Update(float dt)
{
	Object::Update(dt);
}

void Cylinder::Draw(Shader* shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Cylinder::Load()
{
    std::vector<float> unitVertices = getUnitCircleVertices();
    std::vector<float> vertices;
    //vertices.reserve(864);

    glm::vec3 color = GetColor();

    constexpr float height = 1.0f;
    constexpr int sectorCount = 72;
    constexpr float radius = 1.0f;


    // put side vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k + 1];
            float uz = unitVertices[k + 2];
            // position vector
            vertices.push_back(ux * radius);             // vx
            vertices.push_back(uy * radius);             // vy
            vertices.push_back(h);                       // vz
            vertices.push_back(color.x);
            vertices.push_back(color.y);
            vertices.push_back(color.z);
        }
    }

    // the starting index for the base/top surface
    //NOTE: it is used for generating indices later
    int baseCenterIndex = (int)vertices.size() / 3;
    int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

    // put base and top vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float nz = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        vertices.push_back(0);     vertices.push_back(0);     vertices.push_back(h);
        
        for (int j = 0, k = 0; j < sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k + 1];
            // position vector
            vertices.push_back(ux * radius);             // vx
            vertices.push_back(uy * radius);             // vy
            vertices.push_back(h);                       // vz
            vertices.push_back(color.x);
            vertices.push_back(color.y);
            vertices.push_back(color.z);
        }
    }

    std::vector<unsigned int> indices;
    int k1 = 0;                         // 1st vertex index at base
    int k2 = sectorCount + 1;           // 1st vertex index at top

    // indices for the side surface
    for (int i = 0; i < sectorCount; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        // k2 => k1+1 => k2+1
        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);
    }

    // indices for the base surface
    //NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
    //      please see the previous code snippet
    for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else // last triangle
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + 1);
            indices.push_back(k);
        }
    }

    // indices for the top surface
    for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if (i < sectorCount - 1)
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else // last triangle
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(topCenterIndex + 1);
        }
    }

    mVertexArray = new VertexArray(vertices.data(), vertices.size() / 6, indices.data(), indices.size());
}


std::vector<float> Cylinder::getUnitCircleVertices()
{
    const float sectorCount = 72;
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y
        unitCircleVertices.push_back(0);                // z
    }
    return unitCircleVertices;
}


