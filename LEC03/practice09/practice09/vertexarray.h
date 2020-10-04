#pragma once

typedef unsigned int GLuint;

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();
	
	void SetActive();

	GLuint GetNumIndices() const { return num_indices_; }
	GLuint GetNumVertices() const { return num_verts_; }
private:
	GLuint num_verts_;
	GLuint num_indices_;
	GLuint vertex_buffer_;
	GLuint index_buffer_;
	GLuint vertex_array_;
};

VertexArray* CreateVertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices);


