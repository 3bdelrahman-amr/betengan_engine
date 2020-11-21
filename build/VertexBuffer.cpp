#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {

}
void VertexBuffer::create(void *data,unsigned int size)
{
	glGenBuffers(1,  &RenderId);
	glBindBuffer(GL_ARRAY_BUFFER, RenderId);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &RenderId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, RenderId);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
