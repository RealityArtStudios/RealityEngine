#pragma once
#include "Window.h"
#include "imgui.h"
#include <chrono>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

class Application {
public:
    Application();
    ~Application();
    bool Initialize();
    void Run();
    void Shutdown();

private:
    void SetupTriangle();
    void CreateShaders();
    void CheckCompileErrors(unsigned int shader, const std::string& type);

    Window m_Window;
    ImVec4 m_ClearColor;
    std::chrono::high_resolution_clock::time_point m_LastTime;
    unsigned int m_VAO, m_VBO, m_ShaderProgram;
    static const char* vertexShaderSource;
    static const char* fragmentShaderSource;
};