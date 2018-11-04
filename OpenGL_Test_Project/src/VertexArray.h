#pragma once
#include "Macros.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include <GL/glew.h>

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer& vbo, const BufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};