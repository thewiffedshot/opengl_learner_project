#pragma once
#include "Test.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GLProgram.h"
#include "Uniform.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_glfw.h"

namespace test
{
	class TestShaderBlending : public Test
	{
	public:
		TestShaderBlending(GLFWwindow* window, ImGuiContext* gui);
		~TestShaderBlending();

		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGuiRender() override;
	private:
		int windowWidth, windowHeight;

		float tri2Dpositions[16] = {			
			-0.4f, -0.35f,  0.0f,  0.0f,
			 0.8f, -0.35f,  1.0f,  0.0f,
			 0.4f,  0.35f,  1.0f,  1.0f,
			-0.8f,  0.35f,  0.0f,  1.0f
		};

		unsigned int indices[6] = {			
			0, 1, 2,
			2, 3, 0
		};

		ImGuiContext* guiContext;

		VertexBuffer* vbo;
		IndexBuffer* ibo;

		BufferLayout* layout;

		VertexArray* va;

		Shader testShaders[2] =														
		{
			Shader(GL_VERTEX_SHADER, "res/shaders/Basic2.shader"),
			Shader(GL_FRAGMENT_SHADER, "res/shaders/Basic2.shader")
		};

		Shader testShaders2[2] =													
		{
			Shader(GL_VERTEX_SHADER, "res/shaders/Basic.shader"),
			Shader(GL_FRAGMENT_SHADER, "res/shaders/Basic.shader")
		};

		float slopeIncrement;
		bool clockwise;
		unsigned long count;

		float color1[4];
		float color2[4];
		float windowSize[2];
		float slope;
		int switched;

		bool show_demo_window = true;
		bool show_another_window = false;

		glm::mat4 projMatrix;

		Texture* t1;
		unsigned int tslot;

		GLProgram* program;
		GLProgram* secondProgram;

		Uniform* tslot_t1;
		Uniform* c1;
		Uniform* c2;
		Uniform* WindowSize;
		Uniform* SlopeBounds;
		Uniform* ColorSwitched;
		Uniform* MVP;
	};
}