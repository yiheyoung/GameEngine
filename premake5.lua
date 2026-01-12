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
IncludeDir["ImGui"] = "GameEngine/vendor/imgui"              -- Add ImGui include directory to the table

-- Include the premake file for GLFW
include "GameEngine/vendor/GLFW"
-- Include the premake file for Glad
include "GameEngine/vendor/Glad"
-- Include the premake file for ImGui
include "GameEngine/vendor/imgui"

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "GameEngine/src/gepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",     -- Use the include directory from the table
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links                                           -- Link static libraries
	{
		"GLFW",          -- Link the GLFW library
		"Glad",          -- Link the Glad library
		"ImGui",         -- Link the ImGui library
		"opengl32.lib"   -- Link the OpenGL library for Windows
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"GameEngine/src"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

		filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"
	
		filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "On"
