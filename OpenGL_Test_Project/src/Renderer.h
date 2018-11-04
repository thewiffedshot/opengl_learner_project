#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <string>
#include "Macros.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GLProgram.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, GLProgram& program) const;
};
