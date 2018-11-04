#pragma once
#include "Macros.h"
#include <GL/glew.h>

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	bool initialized = false;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer();												// Object not instatiated via this contstructor. Acting as stack allocation placeholder. Do not use.	
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetVertexCount() const
	{
		return m_Count;
	}

	inline void SetVertexCount(unsigned long vCount)
	{
		m_Count = vCount;
	}
};