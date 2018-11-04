#include "GLProgram.h"

GLProgram::GLProgram(Shader* shaders, unsigned int count)
{
	GLCall(m_RendererID = glCreateProgram());
	Attach(shaders, count);
	Bind();
}

GLProgram::GLProgram()
{
	GLCall(m_RendererID = glCreateProgram());
}

GLProgram::~GLProgram()
{
	GLCall(glUseProgram(m_RendererID));

	for (Shader* shader : m_AttachedShaders)
	{
		GLCall(glDeleteShader(shader->GetHandle()));
	}

	GLCall(glDeleteProgram(m_RendererID));
	delete[] m_UniformLocations;
}

void GLProgram::Bind()
{
	GLCall(glUseProgram(m_RendererID));
	RefreshUniforms();
}

void GLProgram::Unbind()
{
	GLCall(glUseProgram(0));
}

void GLProgram::Attach(Shader& shader)
{
	if (shader.Attachable())
	{
		GLCall(glAttachShader(m_RendererID, shader.GetHandle()));
		m_AttachedShaders.push_back(&shader);
	}
	else
		std::cout << "Shader of type '" << shader.GetType() << "' and handle '" << shader.GetHandle() << "' is not attachable. It was left off the final program with handle '" << m_RendererID << "'" << std::endl;

	LinkProgram();
}

void GLProgram::Attach(Shader shaders[], unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		if (shaders[i].Attachable())
		{
			GLCall(glAttachShader(m_RendererID, shaders[i].GetHandle()));
			m_AttachedShaders.push_back(&shaders[i]);
		}
		else
			std::cout << "Shader of type '" << shaders[i].GetType() << "' and handle '" << shaders[i].GetHandle() << "' is not attachable. It was left off the final program with handle '" << m_RendererID << "'" << std::endl;
	}

	LinkProgram();
}

void GLProgram::Detach(Shader& shader)
{
	unsigned int count = m_AttachedShaders.size();

	for (unsigned int i = 0; i < count; i++)
	{
		if (shader.SameInstance(*m_AttachedShaders[i]))
		{
			m_AttachedShaders.erase(m_AttachedShaders.begin() + i);
			GLCall(glDetachShader(m_RendererID, m_AttachedShaders[i]->GetHandle()));
		}
	}

	LinkProgram();
}

void GLProgram::Detach()
{
	unsigned int count = m_AttachedShaders.size();

	for (unsigned int i = 0; i < count; i++)
	{
		m_AttachedShaders.erase(m_AttachedShaders.begin() + i);
		GLCall(glDetachShader(m_RendererID, m_AttachedShaders[i]->GetHandle()));
	}

	LinkProgram();
}

void GLProgram::LinkProgram()
{
	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));

	for (Shader* shader : m_AttachedShaders)
	{
		GLCall(glDeleteShader(shader->GetHandle()));
	}
}

void GLProgram::AttachUniform(Uniform& uniform)
{
	m_Uniforms.push_back(&uniform);
	m_UniformLocations = GetUniformLocations();
	ParseUniform(&uniform);
}

void GLProgram::DeleteUniform(const std::string& identifier)
{
	unsigned int i = 0;

	for (Uniform* u : m_Uniforms)
	{
		if (u->GetName() == identifier)
		{
			m_Uniforms.erase(m_Uniforms.begin() + i);
			break;
		}

		i++;
	}

	m_UniformLocations = GetUniformLocations();
}


int* GLProgram::GetUniformLocations()
{
	if (m_UniformLocations != nullptr)
	{
		delete[] m_UniformLocations;
		m_UniformLocations = nullptr;
	}

	unsigned int count = m_Uniforms.size();

	if (count != 0)
	{
		int* ptr = new int[count];

		for (unsigned int i = 0; i < count; i++)
		{
			GLCall(ptr[i] = glGetUniformLocation(m_RendererID, m_Uniforms[i]->GetName().c_str()));
			ASSERT(ptr[i] != -1);
		}

		return ptr;
	}
	else
		return nullptr;
}

void GLProgram::ParseUniform(Uniform* uniform)
{
	unsigned int locationOffset = 0;

	for (Uniform* u : m_Uniforms)
	{
		if (u == uniform)
			break;

		locationOffset++;
	}

	if (locationOffset >= m_Uniforms.size())
	{
		std::cout << "No uniform with identifier '" << uniform->GetName() << "' present. It was not parsed." << std::endl;
		return;
	}

	UniformType type = uniform->GetType();
	void* data = nullptr;

	data = uniform->GetData();

	switch (type)
	{
		case FLOAT:
			GLCall(glUniform1f(*(m_UniformLocations + locationOffset), *((float*)data)));
			break;
		case FLOAT2:
			GLCall(glUniform2f(*(m_UniformLocations + locationOffset), *(((float*)data)), *(((float*)data) + 1)));
			break;
		case FLOAT3:
			GLCall(glUniform3f(*(m_UniformLocations + locationOffset), *(((float*)data)), *(((float*)data) + 1), *(((float*)data) + 2)));
			break;
		case FLOAT4:
			GLCall(glUniform4f(*(m_UniformLocations + locationOffset), *(((float*)data)), *(((float*)data) + 1), *(((float*)data) + 2), *(((float*)data) + 3)));
			break;
		case DOUBLE:
			GLCall(glUniform1d(*(m_UniformLocations + locationOffset), *((double*)data)));
			break;
		case DOUBLE2:
			GLCall(glUniform2d(*(m_UniformLocations + locationOffset), *(((double*)data)), *(((double*)data) + 1)));
			break;
		case DOUBLE3:
			GLCall(glUniform3d(*(m_UniformLocations + locationOffset), *(((double*)data)), *(((double*)data) + 1), *(((double*)data) + 2)));
			break;
		case DOUBLE4:
			GLCall(glUniform4d(*(m_UniformLocations + locationOffset), *(((double*)data)), *(((double*)data) + 1), *(((double*)data) + 2), *(((double*)data) + 3)));
			break;
		case INT:
			GLCall(glUniform1i(*(m_UniformLocations + locationOffset), *((int*)data)));
			break;
		case INT2:
			GLCall(glUniform2i(*(m_UniformLocations + locationOffset), *(((int*)data)), *(((int*)data) + 1)));
			break;
		case INT3:
			GLCall(glUniform3i(*(m_UniformLocations + locationOffset), *(((int*)data)), *(((int*)data) + 1), *(((int*)data) + 2)));
			break;
		case INT4:
			GLCall(glUniform4i(*(m_UniformLocations + locationOffset), *(((int*)data)), *(((int*)data) + 1), *(((int*)data) + 2), *(((int*)data) + 3)));
			break;
		case fMAT2x2:
			GLCall(glUniformMatrix2fv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (float*)data));
			break;
		case fMAT3x3:
			GLCall(glUniformMatrix3fv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (float*)data));
			break;
		case fMAT4x4:
			GLCall(glUniformMatrix4fv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (float*)data));
			break;
		case dMAT2x2:
			GLCall(glUniformMatrix2dv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (double*)data));
			break;
		case dMAT3x3:
			GLCall(glUniformMatrix2dv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (double*)data));
			break;
		case dMAT4x4:
			GLCall(glUniformMatrix2dv(*(m_UniformLocations + locationOffset), 1, uniform->Transpose(), (double*)data));
			break;
		default:
			std::cout << "Invalid uniform type. Can't parse. ProgramID: '" << m_RendererID << "' UniformID: '" << m_Uniforms[locationOffset]->GetName() << "'" << std::endl;
			break;
	}
}

void GLProgram::RefreshUniforms()
{
	for (Uniform* u : m_Uniforms)
	{
		ParseUniform(u);
	}
}