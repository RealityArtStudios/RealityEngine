#pragma once
#include "Window.h"
#include "RHI/Common/RenderingContext.h"  
#include "RHI/Common/VertexArray.h"      
#include "RHI/Common/Shader.h"  
#include <chrono>
#include <imgui.h>

class Application {
public:
    Application();
    ~Application();
    bool Initialize();
    void Run();
    void Shutdown();

private:
    void SetupTriangle();

    Window m_Window;
    Renderer::RenderingContext* m_RenderingContext;
    Renderer::VertexArray* m_VertexArray;
    Renderer::Shader* m_Shader;
    glm::vec4 m_ClearColor;
    std::chrono::high_resolution_clock::time_point m_LastTime;
};