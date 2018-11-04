#pragma once
#include "Macros.h"
#include <vector>

struct BufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int SizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<BufferLayoutElement> m_Elements;
	unsigned int m_Stride;
public:
	BufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back( { GL_FLOAT, count, GL_FALSE } );
		m_Stride += BufferLayoutElement::SizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
		m_Stride += BufferLayoutElement::SizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back( { GL_UNSIGNED_BYTE, count, GL_TRUE } );
		m_Stride += BufferLayoutElement::SizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline unsigned int GetStride() const
	{
		return m_Stride;
	}

	inline const std::vector<BufferLayoutElement>& GetElements() const
	{
		return m_Elements;
	}
};