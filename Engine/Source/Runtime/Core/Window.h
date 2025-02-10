#pragma once

#define GLFW_INCLUDE_NONE // ? Prevent GLFW from including OpenGL headers
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();

    bool Initialize(int width, int height, const char* title);
    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;
    GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
    static void GLFWErrorCallback(int error, const char* description);

    GLFWwindow* m_Window;
};