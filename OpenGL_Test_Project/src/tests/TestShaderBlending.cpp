#include "TestShaderBlending.h"
#include "Macros.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_glfw.h"
#include "Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

test::TestShaderBlending::TestShaderBlending(GLFWwindow* window, ImGuiContext* gui)
	: slopeIncrement(0.04f), count(0), slope(0.0f), switched(false), color1{ 0.0f, 1.0f, 0.0f, 0.4f },
	  color2{ 1.0f, 0.0f, 0.0f, 0.4f }, tslot(0), guiContext(gui)
{
	program = new GLProgram;
	secondProgram = new GLProgram;

	vbo = new VertexBuffer(tri2Dpositions, sizeof(tri2Dpositions));
	ibo = new IndexBuffer(indices, 6);
	layout = new BufferLayout;
	va = new VertexArray;

	windowSize[0] = windowWidth;
	windowSize[1] = windowHeight;

	layout->Push<float>(2);
	layout->Push<float>(2);
	va->AddBuffer(*vbo, *layout);

	program->Attach(testShaders[0]);
	program->Attach(testShaders[1]);
	secondProgram->Attach(testShaders2[0]);
	secondProgram->Attach(testShaders2[1]);

	c1 = new Uniform(color1, UniformType::FLOAT4, "u_Color", false);					
	c2 = new Uniform(color2, UniformType::FLOAT4, "u_Color2", false);
	WindowSize = new Uniform(windowSize, UniformType::FLOAT2, "u_WindowSize", false);
	SlopeBounds = new Uniform(&slope, UniformType::FLOAT, "u_SlopeBoundary", false);
	ColorSwitched = new Uniform(&switched, UniformType::INT, "u_Switched", false);

	projMatrix = glm::ortho(-1.777778f, 1.777778f, -1.0f, 1.0f, -1.0f, 1.0f);
	MVP = new Uniform(&projMatrix[0][0], UniformType::fMAT4x4, "u_MVP", false);

	t1 = new Texture("res/textures/groundT.png");
	t1->Bind(tslot);
	tslot_t1 = new Uniform(&tslot, UniformType::INT, "u_Texture", false);

	program->Bind();
	program->AttachUniform(*c1);				// Important: Need to rewrite GLProgram code so that it eliminates possible duplicate identifier uniforms from it's 'vector' Uniform cache.
	program->AttachUniform(*c2);
	program->AttachUniform(*WindowSize);
	program->AttachUniform(*SlopeBounds);
	program->AttachUniform(*ColorSwitched);
	program->AttachUniform(*MVP);

	secondProgram->Bind();
	secondProgram->AttachUniform(*tslot_t1);
	secondProgram->AttachUniform(*MVP);
}

test::TestShaderBlending::~TestShaderBlending()
{
	delete program;
	delete secondProgram;

	delete vbo;
	delete ibo;
	delete layout;
	delete va;

	delete t1;

	delete tslot_t1;
	delete c1;
	delete c2;
	delete WindowSize;
	delete SlopeBounds;
	delete ColorSwitched;
	delete MVP;
}

void test::TestShaderBlending::OnUpdate(float deltaTime)
{
}

void test::TestShaderBlending::OnRender(const Renderer& renderer)
{
	renderer.Draw(*va, *ibo, *secondProgram);

	c1->SetData(color1);
	c2->SetData(color2);
	SlopeBounds->SetData(&slope);
	ColorSwitched->SetData(&switched);

	renderer.Draw(*va, *ibo, *program);

	if (!clockwise)
	{
		slope += slopeIncrement;

		if (slope > M_PI)
		{
			slope = 0;
			switched = !switched;
		}
	}
	else if (clockwise)
	{
		slope -= slopeIncrement;

		if (slope < 0)
		{
			slope = M_PI;
			switched = !switched;
		}
	}
}

void test::TestShaderBlending::OnImGuiRender()
{
	ImGui::SetCurrentContext(guiContext);

	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Controls.");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Use this form to control parameters.");					  // Display some text (you can use a format strings too)
	ImGui::Checkbox("Clockwise: ", &clockwise);								  // Edit bools storing our window open/close state

	ImGui::SliderFloat("Increment: ", &slopeIncrement, 0.0f, 1.0f);           // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit4("color 1", (float*)&color1);							  // Edit 4 floats representing a color
	ImGui::ColorEdit4("color 2", (float*)&color2);					          // Edit 4 floats representing a color																			 

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}