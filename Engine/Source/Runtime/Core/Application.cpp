#include "Application.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "RHI/Common/Texture.h"

Application::Application()
    : m_ClearColor(0.45f, 0.55f, 0.60f, 1.00f),
    m_RenderingContext(nullptr),
    m_VertexArray(nullptr),
    m_Shader(nullptr) {
}

Application::~Application() {
    delete m_VertexArray;
    delete m_Shader;
    delete m_RenderingContext;
}

bool Application::Initialize() {
    if (!m_Window.Initialize(1280, 720, "RealityEngine")) {
        return false;
    }

    // Create rendering context
    m_RenderingContext = Renderer::RenderingContext::Create(Renderer::API::OpenGL);
    m_RenderingContext->Init();

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    SetupTriangle();
    m_LastTime = std::chrono::high_resolution_clock::now();

    return true;
}

void Application::SetupTriangle() {
    // Vertex data
    float vertices[] = {
        // Positions          // UVs
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,  // Bottom-left
       0.5f, -0.5f, 0.0f,   1.0f, 0.0f,  // Bottom-right
       0.0f,  0.5f, 0.0f,   0.5f, 1.0f   // Top
    };

    // Index data
    uint32_t indices[] = {
        0, 1, 2 // Triangle
    };

    // Create buffers
    Renderer::VertexBuffer* vb = Renderer::VertexBuffer::Create(vertices, sizeof(vertices));
    Renderer::IndexBuffer* ib = Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    m_VertexArray = Renderer::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vb);
    m_VertexArray->SetIndexBuffer(ib); // Set the index buffer
    m_VertexArray->SetVertexAttributes();

    // Create shaders
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;

        void main() {
            gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;

        }
    )";

    const char* fragmentShaderSrc = R"(
       #version 330 core
    in vec2 TexCoord;
    uniform sampler2D u_Texture;  // Add this line
    out vec4 FragColor;

    void main() {
       FragColor = texture(u_Texture, TexCoord);
    }
    )";

    m_Shader = Renderer::Shader::Create(vertexShaderSrc, fragmentShaderSrc);
}
void Application::Run() {
    Renderer::Texture texture("Engine/Content/Textures/Texturelabs_Wood_260XL.jpg");

    while (!m_Window.ShouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - m_LastTime;
        m_LastTime = currentTime;
        float deltaTime = elapsedTime.count();
        m_Window.PollEvents();

        // Rendering
        m_RenderingContext->SetClearColor(m_ClearColor);
        m_RenderingContext->Clear({ true, true, false });
        texture.Bind(0);

        m_Shader->Bind();
        m_Shader->SetUniform("u_Texture", 0); // Set texture slot

        m_RenderingContext->DrawIndexed(m_VertexArray, 3); // Pass the vertex array here
        m_Shader->Unbind();

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo = true;
        if (show_demo) ImGui::ShowDemoWindow(&show_demo);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.SwapBuffers();
    }
}

void Application::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}