#include "Model.h"
#include <fstream>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

	unsigned long counter = 0;
	unsigned long skips = 0;

	std::vector<unsigned long> checked;
	std::vector<unsigned long> nChecked;

	std::vector<unsigned long> vIndeces;

	for (unsigned long i = 0; i < indeces.size(); i++)
	{
		bool skip = true;

		if (i == 0)
		{
			checked.push_back(indeces[i]);   // Rework this.
			nChecked.push_back(nIndeces[i]);

			for (unsigned long n = 0; n < indeces.size(); n++)
			{
				if (indeces[n] == indeces[i] && nIndeces[n] == nIndeces[i])
				{
					vIndeces.push_back(n);
					break;
				}
			}

			continue;
		}
		
		for (unsigned long j = 0; j < checked.size(); j++)
		{
			if (!(checked[j] == indeces[i] && nChecked[j] == nIndeces[i]))
			{
				skip = false;
			}
			else
			{
				skip = true;

				for (unsigned long n = 0; n < indeces.size(); n++)
				{
					if (indeces[n] == indeces[i] && nIndeces[n] == nIndeces[i])
					{
						vIndeces.push_back(n % checked.size());
						break;
					}
				}

				skips++;
				break;
			}
		}

		if (!skip)
		{
			checked.push_back(indeces[i]);
			nChecked.push_back(nIndeces[i]);

			for (unsigned long n = 0; n < indeces.size(); n++)
			{
				if (indeces[n] == indeces[i] && nIndeces[n] == nIndeces[i])
				{
					vIndeces.push_back(n - skips);
					break;
				}
			}
		}
	}

	std::unique_ptr<float> vertexArray(new float[6 * checked.size()]);
	std::unique_ptr<unsigned int> indexArray(new unsigned int[checked.size() + skips]);
	float vData[3];
	float nData[3];

	for (unsigned int i = 0; i < checked.size(); i++)
	{
		Vector3 vertex = verteces[checked[i] - 1];
		Vector3 vNormal = vNormals[nChecked[i] - 1];

		vData[0] = vertex.x;
		vData[1] = vertex.y;
		vData[2] = vertex.z;

		nData[0] = vNormal.x;
		nData[1] = vNormal.y;
		nData[2] = vNormal.z;

		memcpy(vertexArray.get() + sizeof(vData) / sizeof(float) * counter, vData, sizeof(vData));
		counter++;
		memcpy(vertexArray.get() + sizeof(nData) / sizeof(float) * counter, nData, sizeof(nData));
		counter++;
	}

	unsigned long count = checked.size() + skips;

	for (int i = 0; i < count; i++)
	{
		indexArray.get()[i] = vIndeces[i]; // TODO: Debug the parsing of the index array.
	}

	vbo = new VertexBuffer(vertexArray.get(), sizeof(float) * 6 * checked.size());
	ibo = new IndexBuffer(indexArray.get(), count);
	ibo->SetVertexCount(indeces.size());
	
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
