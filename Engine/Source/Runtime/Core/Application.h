#pragma once
// Main application class
#define GLFW_INCLUDE_NONE  // Prevent GLFW from including OpenGL headers
#include "../../../ThirdParty/Glad/include/glad/glad.h"
#include <GLFW/glfw3.h>    

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <chrono>
// GLFW error callback
static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// Vertex Shader Source
static const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment Shader Source
static const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
    }
)";


class Application {
public:
    Application();
    ~Application();
    bool Initialize();

    void SetupTriangle();

    void CreateShaders();

    void CheckCompileErrors(unsigned int shader, std::string type);

    void Run();

    void Shutdown();
  

private:
    GLFWwindow* window;
    ImVec4 clear_color;
    std::chrono::high_resolution_clock::time_point lastTime;
    unsigned int VAO, VBO, shaderProgram;
};