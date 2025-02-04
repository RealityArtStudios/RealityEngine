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
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment Shader Source
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
    }
)";

// Main application class
class Application {
public:
    Application() : window(nullptr), clear_color(0.45f, 0.55f, 0.60f, 1.00f) {}

    bool Initialize() {
        // Set up GLFW
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        // Set up OpenGL context
        const char* glsl_version = "#version 330 core";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4); // Enable 4x MSAA

        // Create window
        window = glfwCreateWindow(1280, 720, "RealityEngine", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Initialize GLAD (Important)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        // Set up Dear ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        // Set up ImGui style
        ImGui::StyleColorsDark();

        // Set up platform/renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Initialize OpenGL objects
        SetupTriangle();

        // Initialize time tracking
        lastTime = std::chrono::high_resolution_clock::now();

        return true;
    }

    void SetupTriangle() {
        // Triangle vertices
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  // Bottom left
             0.5f, -0.5f, 0.0f,  // Bottom right
             0.0f,  0.5f, 0.0f   // Top
        };

        // Create VAO and VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind and set VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO and VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Compile and link shaders
        CreateShaders();
    }

    void CreateShaders() {
        // Create vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        // Create fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        // Create shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        CheckCompileErrors(shaderProgram, "PROGRAM");

        // Delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void CheckCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
            }
        }
    }

    void Run() {
        while (!glfwWindowShouldClose(window)) {
            // Calculate delta time
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = currentTime - lastTime;
            lastTime = currentTime;
            float deltaTime = elapsedTime.count();

            // Poll events
            glfwPollEvents();

            // Render Triangle
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Show demo window
            static bool show_demo_window = true;
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);
        }
    }

    void Shutdown() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Cleanup GLFW
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    GLFWwindow* window;
    ImVec4 clear_color;
    std::chrono::high_resolution_clock::time_point lastTime;
    unsigned int VAO, VBO, shaderProgram;
};

// Entry point
int main() {
    Application app;
    if (!app.Initialize()) return -1;
    app.Run();
    app.Shutdown();
    return 0;
}
