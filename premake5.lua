workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}                                                  -- Create a table for include directories
IncludeDir["GLFW"] = "GameEngine/vendor/GLFW/include"            -- Add GLFW include directory to the table
IncludeDir["Glad"] = "GameEngine/vendor/Glad/include"            -- Add Glad include directory to the table
IncludeDir["ImGui"] = "GameEngine/vendor/imgui"                  -- Add ImGui include directory to the table
IncludeDir["glm"] = "GameEngine/vendor/glm"                      -- Add glm include directory to the table
IncludeDir["stb_image"] = "GameEngine/vendor/stb_image"          -- Add stb_image include directory to the table

-- Include the premake file for GLFW
include "GameEngine/vendor/GLFW"
-- Include the premake file for Glad
include "GameEngine/vendor/Glad"
-- Include the premake file for ImGui
include "GameEngine/vendor/imgui"

project "GameEngine"
	location "GameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "GameEngine/src/gepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",     -- Use the include directory from the table
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links                                           -- Link static libraries
	{
		"GLFW",          -- Link the GLFW library
		"Glad",          -- Link the Glad library
		"ImGui",         -- Link the ImGui library
		"opengl32.lib"   -- Link the OpenGL library for Windows
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GameEngine/vendor/spdlog/include",
		"GameEngine/src",
		"GameEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"
