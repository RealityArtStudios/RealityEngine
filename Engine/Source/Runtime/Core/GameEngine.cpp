#include "GameEngine.h"
#include "Renderer.h"
#include "ImGuiManager.h"
#include "Window.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Input()
{
}

void GameEngine::Run()
{
    Input();
    Render();
    Update();
}
void GameEngine::Render()
{
    Renderer renderer;
    Window window;
    window.CreateWindoww();

    // Initialize Direct3D
    if (!renderer.CreateDeviceD3D(window.GetHwnd()))
    {
        renderer.CleanupDeviceD3D();
    }

    // Show the window
    ::ShowWindow(window.GetHwnd(), SW_SHOWDEFAULT);
    ::UpdateWindow(window.GetHwnd());


    ImGuiManager imguimanager;
    imguimanager.SetupImGui();
    imguimanager.SetupImGuiStyle();
    // Setup Platform/Renderer backends
    imguimanager.InitImGui(window, renderer);


    renderer.CleanupDeviceD3D();
}

void GameEngine::Update()
{
}
