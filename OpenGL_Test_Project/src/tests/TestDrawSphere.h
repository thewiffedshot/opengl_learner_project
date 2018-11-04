#pragma once
#include "Test.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Model.h"
#include "Camera.h";
#include <string>
#include "GLFW\glfw3.h"
#include <memory>
#include "imgui\imgui.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace test
{
	class TestDrawSphere : public Test
	{
	public:
		TestDrawSphere(GLFWwindow* window, ImGuiContext* gui);
		~TestDrawSphere();

		void OnRender(const Renderer& renderer) override;
		void OnImGuiRender() override;
		void OnUpdate(float deltaTime) override;

	private:
		GLFWwindow* window;
		ImGuiContext* guiContext;
		PointLight light;
		Camera camera;
		Model sphereModel;

		Uniform* ModelMatrix;
		Uniform* ViewMatrix;
		Uniform* ProjMatrix;
		Uniform* MaterialColor;
		Uniform* LightPos;
		Uniform* LightColor;
		Uniform* LightDistance;
		Uniform* LightPower;
		Uniform* AmbientLight;
	};
}