#include "Macros.h"
#include "GL/glew.h"
#include <iostream>

bool GLCheckError(const char* functionLog, const char* sourceFile, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "\n[OpenGL Error " << error << "]: " << functionLog << " : " << sourceFile << " : " << line << std::endl;
		return false;
	}
	return true;
}

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}