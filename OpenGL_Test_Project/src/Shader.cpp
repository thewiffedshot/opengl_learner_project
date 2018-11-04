#include "Shader.h"

Shader::Shader(const unsigned int type, const std::string& filepath)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		m_ShaderType = GL_VERTEX_SHADER;
		break;
	case GL_FRAGMENT_SHADER:
		m_ShaderType = GL_FRAGMENT_SHADER;
		break;
	default:
		ASSERT(0);
		std::cout << "Unrecognized shader type. Defaulting to GL_VERTEX_SHADER..." << std::endl;
		m_ShaderType = GL_VERTEX_SHADER;
		break;
	}
	m_Source = Parse(filepath);

	GLCall(m_RendererID = glCreateShader(m_ShaderType));

	Compile();
}

Shader::Shader()
{

}

std::string Shader::Parse(const std::string& filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream stringStream;
	bool write = false;

	if (m_ShaderType == GL_VERTEX_SHADER)
	{
		while (getline(stream, line))
		{
			if (line.find("#shader vertex") != std::string::npos && write == false)
			{
				write = true;
			}
			else if (line.find("#shader") != std::string::npos && write == true)
			{
				write = false;
			}
			else if (write)
			{
				stringStream << line << "\n";
			}
		}
	}
	else if (m_ShaderType == GL_FRAGMENT_SHADER)
	{
		while (getline(stream, line))
		{
			if (line.find("#shader fragment") != std::string::npos && write == false)
			{
				write = true;
			}
			else if (line.find("#shader") != std::string::npos && write == true)
			{
				write = false;
			}
			else if (write)
			{
				stringStream << line << "\n";
			}
		}
	}
	else
	{
		std::cout << "Couldn't find appropriate shader (Maybe misspelled markup or defaulted type?)... Aborting" << std::endl;
		return nullptr;
	}

	return stringStream.str();
}

void Shader::Compile()
{
	const char* src = m_Source.c_str();

	GLCall(glShaderSource(m_RendererID, 1, &src, nullptr));
	GLCall(glCompileShader(m_RendererID));

	bool state = CompileCheck();
	ASSERT(state);
	m_Attachable = state;
}

void Shader::Recompile(const std::string& filepath)
{
	m_Source = Parse(filepath);
	const char* src = m_Source.c_str();

	GLCall(glShaderSource(m_RendererID, 1, &src, nullptr));    
	GLCall(glCompileShader(m_RendererID));

	bool state = CompileCheck();
	ASSERT(state);
	m_Attachable = state;
}

bool Shader::CompileCheck()
{
	int result;
	GLCall(glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &result)); 													

	if (result == GL_FALSE)							
	{
		int length;
		GLCall(glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &length));		

		char* message = (char*)(alloca(length * sizeof(char)));		      
		GLCall(glGetShaderInfoLog(m_RendererID, length, &length, message));	

		std::cout << "Failed to compile " << (m_ShaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;  
		std::cout << message << std::endl;

		GLCall(glDeleteShader(m_RendererID));  
		return false;
	}

	return true;
}

