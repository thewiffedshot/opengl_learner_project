#pragma once
#include "Macros.h"
#include <GL/glew.h>

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();										// Object not instatiated via this contstructor. Acting as stack allocation placeholder. Do not use.								
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};