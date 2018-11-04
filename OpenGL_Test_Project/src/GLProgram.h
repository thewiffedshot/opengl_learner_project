#pragma once
#include "Macros.h"
#include "Shader.h"
#include "Uniform.h"
#include <vector>
#include <GL/glew.h>
#include <iostream>

class GLProgram
{
private:
	unsigned int m_RendererID;
	std::vector<Shader*> m_AttachedShaders;
	std::vector<Uniform*> m_Uniforms;
	int* m_UniformLocations = nullptr;

	void LinkProgram();
	int* GetUniformLocations();
	void ParseUniform(Uniform* uniform);

public:
	GLProgram(Shader shaders[], unsigned int count);
	GLProgram();
	~GLProgram();

	void Attach(Shader shaders[], unsigned int count);
	void Attach(Shader& shader);
	void Detach(Shader& shader);
	void Detach();

	void AttachUniform(Uniform& uniform);
	void DeleteUniform(const std::string& identifier);
	void RefreshUniforms();

	void Bind();
	void Unbind();

	inline const std::vector<Shader*> AttachedShaders() const
	{
		return m_AttachedShaders;
	}

	inline const unsigned int GetHandle() const
	{
		return m_RendererID;
	}

	inline int GetUniformLocation(Uniform& uniform) const
	{
		for (unsigned int i = 0; i < m_Uniforms.size(); i++)
		{
			if (&uniform == m_Uniforms[i])
			{
				return m_UniformLocations[i];
			}
		}
	}

	inline int GetUniformLocation(std::string& uName) const
	{
		for (unsigned int i = 0; i < m_Uniforms.size(); i++)
		{
			if (m_Uniforms[i]->GetName() == uName)
			{
				return m_UniformLocations[i];
			}
		}
	}
};