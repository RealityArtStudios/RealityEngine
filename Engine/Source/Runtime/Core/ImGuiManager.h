#pragma once
#include <d3d11.h>
#include "Window.h"
#include "Renderer.h"

class ImGuiManager
{
public:

	ImGuiManager();
	~ImGuiManager();

	void SetupImGui();
	void SetupImGuiStyle();
	void InitImGui(Window window, Renderer renderer);
};

