#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "utility\Vectors.h"
#include <string>
#include <sstream>
#include "BufferLayout.h"
#include "VertexArray.h"
#include "lighting\Material.h"
#include "lighting\PointLight.h"
#include "GLProgram.h"
#include "glm\gtc\matrix_transform.hpp"

class Model
{
public:
	Model(const std::string& objPath);
	Model(Vector3 worldPosition, const std::string& objPath);
	Model();
	~Model();

	Material material;

	void ChangeShaders(Shader* shaders, unsigned int count = 2);

	VertexArray* GetVertexArray()
	{
		return va;
	}

	IndexBuffer* GetIndexBuffer()
	{
		return ibo;
	}

	GLProgram* GetProgram()
	{
		return program;
	}

	Vector3 GetPosition() const
	{
		return m_WorldPos;
	}

	unsigned long GetFaces() const
	{
		return m_Faces;
	}

	unsigned long GetVerteces() const
	{
		return m_Verteces;
	}

	glm::mat4 GetModelMatrix() const
	{
		return m_modelMatrix;
	}

	void Translate();
	void Scale(float factor);
	void Translate(Vector3 vec);
	void Rotate(const Vector3 vec, float deg);
	void RotateX(float deg);
	void RotateY(float deg);
	void RotateZ(float deg);

private:
	Vector3 m_WorldPos = { 0.0f, 0.0f, 0.0f };
	unsigned long m_Faces = -1;
	unsigned long m_Verteces = -1;

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	Shader shaders[2] = 
	{
		Shader(GL_VERTEX_SHADER, "res/shaders/Diffuse.shader"),
		Shader(GL_FRAGMENT_SHADER, "res/shaders/Diffuse.shader")
	};

	GLProgram* program;

	VertexBuffer* vbo;
	IndexBuffer* ibo;

	BufferLayout* layout;
	VertexArray* va;

	void Update();
	void Parse(const std::string& vertexData, const std::string& indexData, const std::string& normalData, const std::string& normalIndexData);
	
}; 