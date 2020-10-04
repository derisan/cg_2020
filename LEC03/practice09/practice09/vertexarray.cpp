#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:num_verts_(numVerts)
	, num_indices_(numIndices)
{
	glGenVertexArrays(1, &vertex_array_);
	glBindVertexArray(vertex_array_);

	glGenBuffers(1, &vertex_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glBufferData(GL_ARRAY_BUFFER, num_verts_ * 3 * sizeof(float), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_ * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertex_buffer_);
	glDeleteBuffers(1, &index_buffer_);
	glDeleteVertexArrays(1, &vertex_array_);
}

void VertexArray::SetActive()
{
	glBindVertexArray(vertex_array_);
}

VertexArray* CreateVertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
{
	VertexArray* vp(new VertexArray(verts, numVerts, indices, numIndices));
	return vp;
}