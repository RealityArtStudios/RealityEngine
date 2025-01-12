#pragma once
#include <d3d11.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <tchar.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Window.h"

class Renderer
{
public:

	Renderer();
	~Renderer();

	// Data
	 ID3D11Device* g_pd3dDevice;
	 ID3D11DeviceContext* g_pd3dDeviceContext;
	 IDXGISwapChain* g_pSwapChain;
	 bool                     g_SwapChainOccluded;
	 ID3D11RenderTargetView* g_mainRenderTargetView;
	// Forward declarations of helper functions
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
};

