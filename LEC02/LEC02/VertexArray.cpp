#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray()
	: _numVerts(0),
	_numIndices(0)
{
}

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:_numVerts(numVerts)
	, _numIndices(numIndices)
{
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 3 * sizeof(float), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3,
	//	reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_indexBuffer);
	glDeleteVertexArrays(1, &_vertexArray);
}

void VertexArray::use()
{
	glBindVertexArray(_vertexArray);
}

VertexArray* createVertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
{
	VertexArray* vp(new VertexArray(verts, numVerts, indices, numIndices));
	return vp;
}