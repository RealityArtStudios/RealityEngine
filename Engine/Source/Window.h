#pragma once
#include "imgui.h"
#include "Windows.h"

static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;

class Window
{
public:

	Window();
	~Window();

	UINT GetReSizeWidth() { return g_ResizeWidth; }
	UINT GetReSizeHeight() { return g_ResizeHeight; }

	void CreateWindoww();
	UINT SetReSizeWidth(UINT width);
	UINT SetReSizeHeight(UINT height);

	WNDCLASSEXW GetWc() { return wc; }
	HWND GetHwnd() { return hwnd; }

private:
	WNDCLASSEXW wc;
	HWND hwnd;
};

