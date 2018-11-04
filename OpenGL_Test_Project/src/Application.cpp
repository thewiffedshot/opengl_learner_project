#include "Renderer.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Macros.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_glfw.h"
#include "tests\Test.h"
#include "tests\TestShaderBlending.h"
#include "tests\TestDrawSphere.h"
#include "Model.h"

#define _USE_MATH_DEFINES
#include <math.h>

int main(void)
{
	GLFWwindow* window;
	ImGuiContext* guiContext;

	if (!glfwInit())
		return -1;

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "OpenGL_Test", NULL, NULL);			// Window with OpenGL context is created but context is not set to current.

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);												// Setting the window's OpenGL context before initializing GLEW is critical.
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)													// GLEW needs to be initialized before attempting to call any GL functions. Beware of the scary NULL pointers.
		std::cout << "GLEW initialization error. Terminating..." << std::endl;													

	guiContext = ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");										// ImGui is initialized with a hardcoded version of GLSL. Keep this in mind if having compatibility issues.

	ImGui::StyleColorsDark();

	std::cout << glGetString(GL_VERSION) << std::endl;			

	GLCall(glEnable(GL_BLEND));													// Enable blending.
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));					// Set blending function to enable transparency by alpha difference.

	Renderer renderer;

	{
		//test::TestShaderBlending test(window, guiContext);
		test::TestDrawSphere test(window, guiContext);
		//float increment = 0.01f;
		//float value = 0.0f;

		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			//test.lightPos[0] = abs(sin(value)) * 50.0f;
			//test.lightPos[1] = abs(sin(value)) * 50.0f;
			//test.lightPos[2] = abs(cos(value)) * 50.0f;
			//test.LightPos->SetData(test.lightPos);
			//value += increment;

			test.OnRender(renderer);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			test.OnImGuiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}