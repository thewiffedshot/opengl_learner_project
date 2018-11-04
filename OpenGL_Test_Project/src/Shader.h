#pragma once
#include "Macros.h"
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <iostream>

class Shader
{
private:
	unsigned int m_RendererID;
	unsigned int m_ShaderType;
	bool m_Attachable = false;

	std::string m_Source;

	std::string Parse(const std::string& filepath);
	void Compile();
	bool CompileCheck();

public:
	Shader(const unsigned int type, const std::string& filepath);
	Shader();														// Object not instatiated via this contstructor. Acting as stack allocation placeholder. Do not use.

	void Recompile(const std::string& filepath);

	inline unsigned int GetHandle() const
	{
		return m_RendererID;
	}

	inline bool Attachable() const
	{
		return m_Attachable;
	}

	inline unsigned int GetType() const
	{
		return m_ShaderType;
	}

	inline const std::string GetSource() const
	{
		return m_Source;
	}

	inline bool SameInstance(const Shader& s)
	{
		return (this == &s) ? true : false;
	}
};