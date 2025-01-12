#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <tchar.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Window.h"
#include "ImGuiManager.h"
#include "Renderer.h"
#include <d3d11.h>
#include "Application.h"

// Main code
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow) {
  
    Application app;
    app.Run();
    return 0;
}

// Helper functions
