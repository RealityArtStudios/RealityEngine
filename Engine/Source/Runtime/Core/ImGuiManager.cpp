#include "ImGuiManager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Window.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"

ImGuiManager::ImGuiManager()
{
}

ImGuiManager::~ImGuiManager()
{
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::SetupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
}

void ImGuiManager::SetupImGuiStyle()
{
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
}

void ImGuiManager::InitImGui(Window window, Renderer renderer)
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Initialize player position with 64-bit precision
    Vector3D playerPosition(0.0, 0.0, 0.0);
    Vector3D playerVelocity(1.0, 0.0, 0.0); // Move along x-axis for demonstration
    double playerSpeed = 0.1; // Adjust speed as necessary

    Matrix4x4 matrix;
    Matrix4x4 scaleMatrix;
    Matrix4x4 translationMatrix;
    Matrix4x4 rotationMatrix;

    // Update matrices (this is an example, adjust as needed)
    double scaleValues[4][4] = {
        { 1.2, 0.0, 0.0, 0.0 },
        { 0.0, 1.2, 0.0, 0.0 },
        { 0.0, 0.0, 1.2, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
    scaleMatrix = Matrix4x4(scaleValues);

    double translationValues[4][4] = {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.5, 0.5, 0.5, 1.0 }
    };
    translationMatrix = Matrix4x4(translationValues);

    double rotationValues[4][4] = {
        { cos(0.5), -sin(0.5), 0.0, 0.0 },
        { sin(0.5), cos(0.5), 0.0, 0.0 },
        { 0.0,      0.0,      1.0, 0.0 },
        { 0.0,      0.0,      0.0, 1.0 }
    };
    rotationMatrix = Matrix4x4(rotationValues);

    ImGui_ImplWin32_Init(window.GetHwnd());
    ImGui_ImplDX11_Init(renderer.g_pd3dDevice, renderer.g_pd3dDeviceContext);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    // Variables for the about window
    bool show_about_window = false;
    while (!done)
    {
        {
            // Handle Input
            playerVelocity = Vector3D(0.0, 0.0, 0.0);

            if (GetAsyncKeyState('W') & 0x8000)
                playerVelocity.z += playerSpeed;
            if (GetAsyncKeyState('S') & 0x8000)
                playerVelocity.z -= playerSpeed;
            if (GetAsyncKeyState('A') & 0x8000)
                playerVelocity.x -= playerSpeed;
            if (GetAsyncKeyState('D') & 0x8000)
                playerVelocity.x += playerSpeed;
            if (GetAsyncKeyState(VK_SPACE) & 0x8000)
                playerVelocity.y += playerSpeed;
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
                playerVelocity.y -= playerSpeed;

            // Update player position
            playerPosition += playerVelocity;
        }

        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window being minimized or screen locked
        if (renderer.g_SwapChainOccluded && renderer.g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        renderer.g_SwapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (window.GetReSizeWidth() != 0 && window.GetReSizeHeight() != 0)
        {
            renderer.CleanupRenderTarget();
            renderer.g_pSwapChain->ResizeBuffers(0, window.GetReSizeWidth(), window.GetReSizeHeight(), DXGI_FORMAT_UNKNOWN, 0);
            window.SetReSizeHeight(0);
            window.SetReSizeWidth(0);
            renderer.CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //Render Coordinate Window
        {
            // Update player position using the transformation matrix
            matrix = scaleMatrix * rotationMatrix * translationMatrix;
            Vector3D transformedPosition = matrix * playerPosition;

            // Render Coordinate Window
            {
                ImGui::Begin("Player Information");
                ImGui::Text("Player Position: (%.6f, %.6f, %.6f)", transformedPosition.x, transformedPosition.y, transformedPosition.z);
                ImGui::Text("Player Velocity: (%.6f, %.6f, %.6f)", playerVelocity.x, playerVelocity.y, playerVelocity.z);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }
        }

        // Create the menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close"))
                    done = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                    show_about_window = true;
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        // Show the about window when requested
        if (show_about_window)
        {
            ImGui::Begin("About", &show_about_window);
            ImGui::Text("ImGui DirectX12 Example");
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        renderer.g_pd3dDeviceContext->OMSetRenderTargets(1, &renderer.g_mainRenderTargetView, nullptr);
        renderer.g_pd3dDeviceContext->ClearRenderTargetView(renderer.g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Present
        HRESULT hr = renderer.g_pSwapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
        renderer.g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

}
