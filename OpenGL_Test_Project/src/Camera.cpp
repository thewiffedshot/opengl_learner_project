#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

Camera::Camera(Vector4 worldPosition, float fov, Vector4 lookAt, GLFWwindow* window)
	: m_WorldPos(worldPosition), fov(fov), initialized(true)
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	Look(lookAt);
}

Camera::Camera(Vector4 worldPosition, GLFWwindow * window)
	: initialized(true)
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

Camera::Camera(float fov, GLFWwindow * window)
	: fov(fov), initialized(true)
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

Camera::Camera(GLFWwindow * window)
	: initialized(true)
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projection = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	Update();
}

Camera::Camera()
{
	m_WorldPos = { 26.923f, -7.692f, 20.0f, 1.0f };
	target = { 0.0f, 0.0f, 0.0f, 1.0f };

	Update();
}

Camera::~Camera()
{

}

void Camera::Update()
{
	camDirection = glm::normalize(glm::vec3(m_WorldPos.x, m_WorldPos.y, m_WorldPos.z) - glm::vec3(target.x, target.y, target.z));
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	camRight = glm::normalize(glm::cross(up, camDirection));
	camUp = glm::normalize(glm::cross(camDirection, camRight));
	view = glm::lookAt(glm::vec3(m_WorldPos.x, m_WorldPos.y, m_WorldPos.z), glm::vec3(target.x, target.y, target.z), camUp);
}

void Camera::Initialize(GLFWwindow* window)
{
	initialized = true;
	fov = 60;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projection = glm::perspective(glm::radians(fov), (float)windowWidth / windowHeight, 0.01f, 10000.0f);
	//Update();
}
