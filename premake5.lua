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
------------------------------------------------------------------------------------------------------------------------------------------
group "Engine"
project "RealityEngine"
    location "Engine"
    kind "ConsoleApp"
    language "C++"
    targetdir ("Engine/Binaries/" .. outputdir .. "/")
    objdir ("Engine/Intermediate/" .. outputdir .. "/")

    files
    {
        "Engine/Source/**.h",
        "Engine/Source/**.cpp",
        "Engine/Source/**.hpp",
        "Engine/ThirdParty/GLFW/include/GLFW/glfw3.h",
    "Engine/ThirdParty/Glad/include/glad/glad.h",
        "Engine/ThirdParty/Glad/include/KHR/khrplatform.h",
        "Engine/ThirdParty/Glad/src/glad.c",
        "Engine/ThirdParty/GLFW/include/GLFW/glfw3native.h",
        "Engine/ThirdParty/imgui/imgui.cpp",
		"Engine/ThirdParty/imgui/imgui_demo.cpp",
		"Engine/ThirdParty/imgui/imgui_tables.cpp",
		"Engine/ThirdParty/imgui/imgui_draw.cpp",
		"Engine/ThirdParty/imgui/imgui_tables.cpp",
		"Engine/ThirdParty/imgui/imgui_widgets.cpp",
		"Engine/ThirdParty/imgui/imgui.h",
		"Engine/ThirdParty/imgui/imgui_internal.h",
        "Engine/ThirdParty/imgui/backends/imgui_impl_opengl3.h",
        "Engine/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp",
        "Engine/ThirdParty/imgui/backends/imgui_impl_glfw.h",
        "Engine/ThirdParty/imgui/backends/imgui_impl_glfw.cpp",
"imgui_impl_opengl3_loader.h",
        "Engine/ThirdParty/GLM/glm/**.hpp",
        "Engine/ThirdParty/GLM/glm/**.inl"
        
    }
    includedirs
    {
        "Engine/Source",
        "Engine/ThirdParty/spdlog/include",
        "Engine/ThirdParty/GLFW/include/",
       "Engine/ThirdParty/imgui",
		"Engine/ThirdParty/imgui/backends",
        "Engine/ThirdParty/GLM",
        "Engine/ThirdParty/Glad",
    "Engine/ThirdParty/Glad/include",
    "Engine/ThirdParty/Glad/include/KHR"
    }

    links 
    { 
        "GLFW",
        "Glad",
        "opengl32.lib"
    }
    filter "system:windows"
        cppdialect "C++latest"
        cdialect "C17"
        staticruntime "Off" -- Ensures dynamic runtime linking
        systemversion "latest"
        buildoptions { "/utf-8" }
    filter "configurations:Debug"
        runtime "Debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        defines { "NDEBUG" }
        optimize "On"
group ""
------------------------------------------------------------------------------------------------------------------------------------------
group "ThirdParty"
project "ImGui"
	kind "StaticLib"
	language "C++"
	targetdir ("Engine/ThirdParty/imgui/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Engine/ThirdParty/imgui/Intermediate/" .. outputdir .. "/%{prj.name}")
	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",
        "imgui_impl_opengl3.h",
        "imgui_impl_opengl3_loader.h",
        "imgui_impl_opengl3.cpp",
        "imgui_impl_glfw.h",
        "imgui_impl_glfw.cpp"
	}
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++latest"
		staticruntime "On"
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++latest"
		staticruntime "On"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
------------------------------------------------------------------------------------------------------------------------------------------
project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "off" -- Ensures dynamic runtime linking
    warnings "off"

    targetdir ("Engine/ThirdParty/GLFW/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Engine/ThirdParty/GLFW/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Engine/ThirdParty/GLFW/include/GLFW/glfw3.h",
        "Engine/ThirdParty/GLFW/include/GLFW/glfw3native.h",
        "Engine/ThirdParty/GLFW/src/glfw_config.h",
        "Engine/ThirdParty/GLFW/src/context.c",
        "Engine/ThirdParty/GLFW/src/init.c",
        "Engine/ThirdParty/GLFW/src/input.c",
        "Engine/ThirdParty/GLFW/src/monitor.c",

        "Engine/ThirdParty/GLFW/src/null_init.c",
        "Engine/ThirdParty/GLFW/src/null_joystick.c",
        "Engine/ThirdParty/GLFW/src/null_monitor.c",
        "Engine/ThirdParty/GLFW/src/null_window.c",

        "Engine/ThirdParty/GLFW/src/platform.c",
        "Engine/ThirdParty/GLFW/src/vulkan.c",
        "Engine/ThirdParty/GLFW/src/window.c",
    }

    filter "system:linux"
        pic "On"
        systemversion "latest"

        files
        {
            "Engine/ThirdParty/GLFW/src/x11_init.c",
            "Engine/ThirdParty/GLFW/src/x11_monitor.c",
            "Engine/ThirdParty/GLFW/src/x11_window.c",
            "Engine/ThirdParty/GLFW/src/xkb_unicode.c",
            "Engine/ThirdParty/GLFW/src/posix_module.c",
            "Engine/ThirdParty/GLFW/src/posix_time.c",
            "Engine/ThirdParty/GLFW/src/posix_thread.c",
            "Engine/ThirdParty/GLFW/src/posix_module.c",
            "Engine/ThirdParty/GLFW/src/glx_context.c",
            "Engine/ThirdParty/GLFW/src/egl_context.c",
            "Engine/ThirdParty/GLFW/src/osmesa_context.c",
            "Engine/ThirdParty/GLFW/src/linux_joystick.c"
        }

        defines
        {
            "_GLFW_X11"
        }

    filter "system:macosx"
        pic "On"

        files
        {
            "Engine/ThirdParty/GLFW/src/cocoa_init.m",
            "Engine/ThirdParty/GLFW/src/cocoa_monitor.m",
            "Engine/ThirdParty/GLFW/src/cocoa_window.m",
            "Engine/ThirdParty/GLFW/src/cocoa_joystick.m",
            "Engine/ThirdParty/GLFW/src/cocoa_time.c",
            "Engine/ThirdParty/GLFW/src/nsgl_context.m",
            "Engine/ThirdParty/GLFW/src/posix_thread.c",
            "Engine/ThirdParty/GLFW/src/posix_module.c",
            "Engine/ThirdParty/GLFW/src/osmesa_context.c",
            "Engine/ThirdParty/GLFW/src/egl_context.c"
        }

        defines
        {
            "_GLFW_COCOA"
        }

    filter "system:windows"
        systemversion "latest"
        cdialect "C17"
        files
        {
            "Engine/ThirdParty/GLFW/src/win32_init.c",
            "Engine/ThirdParty/GLFW/src/win32_joystick.c",
            "Engine/ThirdParty/GLFW/src/win32_module.c",
            "Engine/ThirdParty/GLFW/src/win32_monitor.c",
            "Engine/ThirdParty/GLFW/src/win32_time.c",
            "Engine/ThirdParty/GLFW/src/win32_thread.c",
            "Engine/ThirdParty/GLFW/src/win32_window.c",
            "Engine/ThirdParty/GLFW/src/wgl_context.c",
            "Engine/ThirdParty/GLFW/src/egl_context.c",
            "Engine/ThirdParty/GLFW/src/osmesa_context.c"
        }

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "speed"

---------------------------------------------------------------------------------------------
project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    
    targetdir ("Engine/ThirdParty/Glad/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("Engine/ThirdParty/Glad/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Engine/ThirdParty/Glad/include/glad/glad.h",
        "Engine/ThirdParty/Glad/include/KHR/khrplatform.h",
        "Engine/ThirdParty/Glad/src/glad.c"
    }

includedirs
{
    "Engine/ThirdParty/Glad/include",
    "Engine/ThirdParty/Glad/include/KHR"
}

    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
group ""
