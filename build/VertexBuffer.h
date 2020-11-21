#pragma once
#include <glad/gl.h>
class VertexBuffer
{
private:
	unsigned int RenderId;
public:
	VertexBuffer();
	void create(void *data,unsigned int size);
	~VertexBuffer();
	void Bind();
	void UnBind();


};

