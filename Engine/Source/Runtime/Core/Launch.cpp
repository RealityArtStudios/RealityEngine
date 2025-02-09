#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Rendering/DrawCall.hpp"
#include "Rendering/GPUBuffer.hpp"
#include "Rendering/PipelineState.hpp"
#include "Rendering/RenderPass.hpp"
#include <iostream>
#include <chrono>

static void glfw_error_callback(int error, const char* description) {
	std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

class Application {
public:
	Application() : window(nullptr), clear_color(0.45f, 0.55f, 0.60f, 1.00f) {}

	bool Initialize() {
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit()) return false;

		const char* glsl_version = "#version 330 core";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		window = glfwCreateWindow(1280, 720, "RealityEngine", nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			return false;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		SetupTriangle();
		CreateShaders();
		SetupRenderPass();

		lastTime = std::chrono::high_resolution_clock::now();
		return true;
	}

	void SetupTriangle() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		vertexBuffer.Create(GPUBuffer::Vertex, sizeof(vertices), vertices);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void CreateShaders() {
		pipeline.LoadShader(R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )", R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0, 0.5, 0.2, 1.0);
            }
        )");
	}

	void SetupRenderPass() {
		mainDraw.SetPipelineState(&pipeline);
		mainDraw.SetVertexBuffer(&vertexBuffer);
		mainPass.AddDrawCall(mainDraw);
	}

	void Run() {
		while (!glfwWindowShouldClose(window)) {
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> elapsedTime = currentTime - lastTime;
			lastTime = currentTime;
			float deltaTime = elapsedTime.count();

			glfwPollEvents();

			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VAO);
			mainPass.Execute();
			glBindVertexArray(0);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			static bool show_demo_window = true;
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
		}
	}

	void Shutdown() {
		glDeleteVertexArrays(1, &VAO);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

private:
	GLFWwindow* window;
	ImVec4 clear_color;
	std::chrono::high_resolution_clock::time_point lastTime;

	// OpenGL objects
	GLuint VAO;

	// Abstraction layer components
	GPUBuffer vertexBuffer;
	PipelineState pipeline;
	RenderPass mainPass;
	DrawCall mainDraw;
};

int main() {
	Application app;
	if (!app.Initialize()) return -1;
	app.Run();
	app.Shutdown();
	return 0;
}