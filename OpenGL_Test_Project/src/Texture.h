#pragma once
#include "Macros.h"
#include "GL/glew.h"
#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	int m_Width, m_Height, m_BPP;
	unsigned char* m_LocalBuffer;
public:
	Texture(const std::string& filepath, bool keepPixelData = false);
	Texture() { }
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const
	{
		return m_Width;
	}

	inline int GetHeight() const
	{
		return m_Height;
	}
};