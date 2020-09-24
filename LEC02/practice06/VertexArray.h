#pragma once

typedef unsigned int GLuint;

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices = nullptr, unsigned int numIndices = 0);
	~VertexArray();
	
	void use();

	GLuint getNumIndices() const { return _numIndices; }
	GLuint getNumVerts() const { return _numVerts; }
private:
	GLuint _numVerts;
	GLuint _numIndices;
	GLuint _vertexBuffer;
	GLuint _indexBuffer;
	GLuint _vertexArray;
};

VertexArray* createVertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices = nullptr, unsigned int numIndices = 0);


