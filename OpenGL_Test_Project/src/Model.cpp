#include "Model.h"
#include <fstream>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utility\Vertex.h"

#define _USE_MATH_DEFINES
#include <math.h>

static void ParseData(const std::string& data, std::vector<unsigned long>* parsed);
static void ParseData(const std::string& data, std::vector<Vector3>* parsed);

Model::Model(const std::string & objPath)
{
	program = new GLProgram;
	program->Attach(shaders[0]);
	program->Attach(shaders[1]);

	std::string line;

	std::ifstream stream(objPath);

	std::stringstream vertexStream;
	std::stringstream normalStream;
	std::stringstream textureStream;   // TODO
	std::stringstream faceVertexIndexStream;
	std::stringstream faceNormalIndexStream;

	while (getline(stream, line))
	{
		if (line.find("v ") != std::string::npos)
		{
			std::string values = line.substr(2, line.size() - 2);

			vertexStream << values << ' ';
		}
		else if (line.find("vn ") != std::string::npos)
		{
			std::string values = line.substr(3, line.size() - 3);

			normalStream << values << ' ';
		}
		else if (line.find("f ") != std::string::npos)
		{
			int counter = 0;
			std::string values = line.substr(2, line.size() - 2);
			std::stringstream ss;

			bool skip = false;

			for (int i = 0; i < values.size(); i++)
			{
				if (!skip)
				{
					if (values[i] != '/')
					{
						ss << values[i];
					}
					else
					{
						skip = true;
						ss << ' ';

						continue;
					}
				}

				skip = false;
			}

			ss << ' ';

			for (char ch : ss.str())
			{
				if (ch == ' ')
				{
					counter++;

					if (counter % 2 == 0)
						faceVertexIndexStream << ch;
					else if (counter != 1)
						faceNormalIndexStream << ch;
				}
				else
				{
					if (counter % 2 == 0)
					{
						faceVertexIndexStream << ch;
					}
					else
					{
						faceNormalIndexStream << ch;
					}
				}
			}

			faceNormalIndexStream << ' ';
		}
	}

	Parse(vertexStream.str(), faceVertexIndexStream.str(), normalStream.str(), faceNormalIndexStream.str());
}

Model::Model(Vector3 worldPosition, const std::string & objPath)
	: m_WorldPos(worldPosition)
{
	program = new GLProgram;
	program->Attach(shaders[0]);
	program->Attach(shaders[1]);
	
	std::string line;

	std::ifstream stream(objPath);

	std::stringstream vertexStream;
	std::stringstream normalStream;
	std::stringstream textureStream;   // TODO
	std::stringstream faceVertexIndexStream;
	std::stringstream faceNormalIndexStream;

	while (getline(stream, line))
	{
		if (line.find("v ") != std::string::npos)
		{
			std::string values = line.substr(2, line.size() - 2);

			vertexStream << values << ' ';
		}
		else if (line.find("vn ") != std::string::npos)
		{
			std::string values = line.substr(3, line.size() - 3);

			normalStream << values << ' ';
		}
		else if (line.find("f ") != std::string::npos)
		{
			int counter = 0;
			std::string values = line.substr(2, line.size() - 2);
			std::stringstream ss;

			bool skip = false;

			for (int i = 0; i < values.size(); i++)
			{
				if (!skip)
				{
					if (values[i] != '/')
					{
						ss << values[i];
					}
					else
					{
						skip = true;
						ss << ' ';

						continue;
					}
				}

				skip = false;
			}

			ss << ' ';

			for (char ch : ss.str())
			{
				if (ch == ' ')
				{
					counter++;

					if (counter % 2 == 0)
						faceVertexIndexStream << ch;
					else if (counter != 1)
						faceNormalIndexStream << ch;
				}
				else
				{
					if (counter % 2 == 0)
					{
						faceVertexIndexStream << ch;
					}
					else
					{
						faceNormalIndexStream << ch;
					}
				}
			}

			faceNormalIndexStream << ' ';
		}
	}

	Parse(vertexStream.str(), faceVertexIndexStream.str(), normalStream.str(), faceNormalIndexStream.str());
}

Model::Model()
{
	program = new GLProgram;
	program->Attach(shaders[0]);
	program->Attach(shaders[1]);

	std::string objPath = "res/models/monkey.obj";

	std::string line;

	std::ifstream stream(objPath);

	std::stringstream vertexStream;
	std::stringstream normalStream;
	std::stringstream textureStream;   // TODO
	std::stringstream faceVertexIndexStream;
	std::stringstream faceNormalIndexStream;

	unsigned int faceCounter = 0;

	while (getline(stream, line))
	{
		if (line.find("v ") != std::string::npos)
		{
			std::string values = line.substr(2, line.size() - 2);

			vertexStream << values << ' ';
		}
		else if (line.find("vn ") != std::string::npos)
		{
			std::string values = line.substr(3, line.size() - 3);

			normalStream << values << ' ';
		}
		else if (line.find("f ") != std::string::npos)
		{
			int counter = 0;
			std::string values = line.substr(2, line.size() - 2);
			std::stringstream ss;

			bool skip = false;

			for (int i = 0; i < values.size(); i++)
			{
				if (!skip)
				{
					if (values[i] != '/')
					{
						ss << values[i];
					}
					else
					{
						skip = true;
						ss << ' ';

						continue;
					}
				}

				skip = false;
			}

			ss << ' ';

			for (char ch : ss.str())
			{
				if (ch == ' ')
				{
					counter++;

					if (counter % 2 == 0)
						faceVertexIndexStream << ch;
					else if (counter != 1)
						faceNormalIndexStream << ch;
				}
				else
				{
					if (counter % 2 == 0)
					{
						faceVertexIndexStream << ch;
					}
					else
					{
						faceNormalIndexStream << ch;
					}
				}
			}

			faceNormalIndexStream << ' ';
			faceCounter++;
		}
	}

	m_Faces = faceCounter;
	Parse(vertexStream.str(), faceVertexIndexStream.str(), normalStream.str(), faceNormalIndexStream.str());
}

static bool Contains(const std::vector<unsigned long>& vector, unsigned long key)
{
	for (auto num : vector)
	{
		if (num == key) return true;
	}
	
	return false;
}

void Model::Parse(const std::string& vertexData, const std::string& indexData, const std::string& normalData, const std::string& normalIndexData)
{
	std::vector<Vector3> verteces;
	ParseData(vertexData, &verteces);
	std::vector<Vector3> vNormals;
	ParseData(normalData, &vNormals);
	std::vector<unsigned long> indeces;
	ParseData(indexData, &indeces);
	std::vector<unsigned long> nIndeces;
	ParseData(normalIndexData, &nIndeces);

	m_Verteces = verteces.size();

	std::vector<Vertex> verts;

	std::vector<unsigned long> vIndeces;

	unsigned long skips = 0;

	verts.push_back(Vertex(verteces[indeces[0]], vNormals[vIndeces[0]], 0));
	vIndeces.push_back(0);

	for (unsigned long i = 1; true; i++)
	{
		Vertex vert = verts[i];

		if (vert.vertex != verteces[indeces[i - skips]] || vert.normal != vNormals[vIndeces[i - skips]])
		{
			verts.push_back(Vertex(verteces[indeces[i - skips]], vNormals[nIndeces[i - skips]], i + skips));
			vIndeces.push_back(i + skips);
		}
		else if (vert.vertex == verteces[indeces[i - skips]] && vert.normal == vNormals[vIndeces[i - skips]])
		{
			for (Vertex v : verts)
			{
				if (v.vertex == verteces[indeces[i - skips]], v.normal == vNormals[nIndeces[i - skips]])
				{
					vIndeces.push_back(v.index);
				}
			}
			skips++;
		}
		else
		{
			break;
		}
	}

	std::unique_ptr<float> vertexArray(new float[6 * verts.size()]);
	std::unique_ptr<unsigned int> indexArray(new unsigned int[vIndeces.size()]);
	float vData[3];
	float nData[3];

	unsigned long counter = 0;

	for (unsigned int i = 0; i < verts.size(); i++)
	{
		vData[0] = verts[i].vertex.x;
		vData[1] = verts[i].vertex.y;
		vData[2] = verts[i].vertex.z;

		nData[0] = verts[i].normal.x;
		nData[1] = verts[i].normal.y;
		nData[2] = verts[i].normal.z;

		memcpy(vertexArray.get() + sizeof(vData) / sizeof(float) * counter, vData, sizeof(vData));
		counter++;
		memcpy(vertexArray.get() + sizeof(nData) / sizeof(float) * counter, nData, sizeof(nData));
		counter++;
	}

	unsigned long count = vIndeces.size();

	for (int i = 0; i < count; i++)
	{
		indexArray.get()[i] = vIndeces[i]; // TODO: Debug the parsing of the index array.
	}

	vbo = new VertexBuffer(vertexArray.get(), sizeof(float) * 6 * verts.size());
	ibo = new IndexBuffer(indexArray.get(), count);
	ibo->SetVertexCount(count);
	
	layout = new BufferLayout;
	layout->Push<float>(3);
	layout->Push<float>(3);
	
	va = new VertexArray;
	va->AddBuffer(*vbo, *layout);
}

static void ParseData(const std::string& data, std::vector<Vector3>* parsed)
{
	int counter = 0;
	float vData[3];

	std::stringstream ph;

	for (unsigned long i = 0; i < data.size(); i++)
	{
		if (data[i] == ' ')
		{
			vData[counter % 3] = std::stof(ph.str());
			counter++;
			ph.str("");

			if (counter % 3 == 0)
			{
				parsed->push_back({ vData[0], vData[1], vData[2] });
			}
		}
		else
		{
			ph << data[i];
		}
	}
}

static void ParseData(const std::string& data, std::vector<unsigned long>* parsed)
{
	std::stringstream ph;

	for (unsigned long i = 0; i < data.size(); i++)
	{
		if (data[i] == ' ')
		{
			float data = std::stof(ph.str());

			parsed->push_back(data);

			ph.str("");
		}
		else
		{
			ph << data[i];
		}
	}
}

void Model::Translate(Vector3 vec)
{
	m_WorldPos += vec;

	m_modelMatrix[3][0] += vec.x;
	m_modelMatrix[3][1] += vec.y;
	m_modelMatrix[3][2] += vec.z;
}

void Model::Translate()
{
	m_modelMatrix[0][3] = m_WorldPos.x;
	m_modelMatrix[1][3] = m_WorldPos.y;
	m_modelMatrix[2][3] = m_WorldPos.z;
}

void Model::Scale(float factor)
{
	m_modelMatrix[0][0] *= factor;
	m_modelMatrix[1][1] *= factor;
	m_modelMatrix[2][2] *= factor;
}

void Model::Rotate(const Vector3 vec, float deg)
{
	const glm::mat4 modelMatrix = m_modelMatrix;

	m_modelMatrix = glm::rotate(modelMatrix, deg, glm::vec3(vec.x, vec.y, vec.z));
}

void Model::RotateX(float deg)
{
	const glm::mat4 modelMatrix = m_modelMatrix;

	m_modelMatrix = glm::rotate(modelMatrix, deg, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Model::RotateY(float deg)
{
	const glm::mat4 modelMatrix = m_modelMatrix;

	m_modelMatrix = glm::rotate(modelMatrix, deg, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Model::RotateZ(float deg)
{
	const glm::mat4 modelMatrix = m_modelMatrix;

	m_modelMatrix = glm::rotate(modelMatrix, deg, glm::vec3(0.0f, 0.0f, 1.0f));
}

Model::~Model()
{
	delete vbo;
	delete ibo;
	delete va;
	delete layout;
	delete program;
}

void Model::ChangeShaders(Shader * shaders, unsigned int count)
{
	program->Detach();
	program->Attach(shaders, count);
}
