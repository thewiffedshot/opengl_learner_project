#pragma once
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "utility\Vectors.h"
#include "GLFW\glfw3.h"

class Camera
{
public:
	Camera(Vector4 worldPosition, float fov, Vector4 lookAt, GLFWwindow* window);
	Camera(Vector4 worldPosition, GLFWwindow* window);
	Camera(float fov, GLFWwindow* window);
	Camera(GLFWwindow* window);
	Camera();
	~Camera();

	void Initialize(GLFWwindow* window);

	glm::mat4 GetViewMatrix() const
	{
		return view;
	}

	glm::mat4 GetProjectionMatrix() const
	{
		return projection;
	}

	Vector4 GetPosition() const
	{
		return m_WorldPos;
	}

	void Translate(Vector4 vec)
	{
		m_WorldPos.x = vec.x;
		m_WorldPos.y = vec.y;
		m_WorldPos.z = vec.z;
		m_WorldPos.w = vec.w;
		Update();
	}

	void Look(Vector4 vec)
	{
		target.x = vec.x;
		target.y = vec.y;
		target.z = vec.z;
		target.w = vec.w;
		Update();
	}

	void Update();
private:
	Vector4 m_WorldPos = { 120.0f, 20.0f, 20.0f, 1.0f };
	Vector4 target = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec3 camDirection; 
	glm::vec3 up; 
	glm::vec3 camRight; 
	glm::vec3 camUp; 

	float fov = 120;
	int windowWidth;
	int windowHeight;
	bool initialized = false;

	glm::mat4 view = glm::lookAt(glm::vec3(m_WorldPos.x, m_WorldPos.y, m_WorldPos.z), glm::vec3(target.x, target.y, target.z), camUp);
	glm::mat4 projection;
	
};