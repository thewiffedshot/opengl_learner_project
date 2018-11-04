#pragma once
#ifdef _DEBUG
#define ASSERT(x)\
	 if(!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLCheckError(#x, __FILE__, __LINE__))
#else
#define ASSERT(x)
#define GLCall(x) x
#endif

void GLClearError();
bool GLCheckError(const char* functionLog, const char* sourceFile, int line);