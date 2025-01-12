workspace "RealityEngine"
	architecture "x64"
	startproject "RealityEngine"

	configurations
	{
		"Debug",
		"DebugGame",
		"Development",
		"Shipping",
		"Test",
		"Release"
	}
outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

project "RealityEngine"
	location "Engine"
	kind "WindowedApp"
	language "C++"
	targetdir ("Engine/Binaries/" .. outputdir .. "/")
	objdir ("Engine/Intermediate/" .. outputdir .. "/")

	files
	{
		"Engine/Source/**.h",
		"Engine/Source/**.cpp",
		"Engine/ThirdParty/imgui/backends/imgui_impl_dx11.cpp",
		"Engine/ThirdParty/imgui/backends/imgui_impl_dx12.cpp",
		"Engine/ThirdParty/imgui/backends/imgui_impl_win32.cpp",
		"Engine/ThirdParty/imgui/imgui.cpp",
		"Engine/ThirdParty/imgui/imgui_demo.cpp",
		"Engine/ThirdParty/imgui/imgui_tables.cpp",
		"Engine/ThirdParty/imgui/imgui_draw.cpp",
		"Engine/ThirdParty/imgui/imgui_tables.cpp",
		"Engine/ThirdParty/imgui/imgui_widgets.cpp",
		"Engine/ThirdParty/imgui/backends/imgui_impl_dx11.h",
		"Engine/ThirdParty/imgui/backends/imgui_impl_dx12.h",
		"Engine/ThirdParty/imgui/backends/imgui_impl_win32.h",
		"Engine/ThirdParty/imgui/imgui.h",
		"Engine/ThirdParty/imgui/imgui_internal.h"
	}

	includedirs
	{
		"Engine/ThirdParty/spdlog/include",
		"Engine/ThirdParty/imgui",
		"Engine/ThirdParty/imgui/backends"
	}

	links 
	{ 
		"dxgi.lib",
		"d3d11.lib",
		"d3d12.lib"
	}
	filter "system:windows"
		cppdialect "C++20"
        cdialect "C17"
		staticruntime "On"
		systemversion "latest"

		 -- Add the /utf-8 compiler flag for Unicode support
		 buildoptions { "/utf-8" }
		 
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
