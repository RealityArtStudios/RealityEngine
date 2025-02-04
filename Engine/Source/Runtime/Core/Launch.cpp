#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

// GLFW error callback
static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

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
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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

        // Initialize time tracking
        lastTime = std::chrono::high_resolution_clock::now();

        return true;
    }

    void Run() {
        while (!glfwWindowShouldClose(window)) {
            // Calculate delta time using std::chrono
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = currentTime - lastTime;
            lastTime = currentTime;
            float deltaTime = elapsedTime.count();

            // Poll events
            glfwPollEvents();

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
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);
        }
    }

    void Shutdown() {
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
};

// Entry point
int main(int, char**) {
    Application app;
    if (!app.Initialize()) {
        return -1;
    }
    app.Run();
    app.Shutdown();
    return 0;
}
