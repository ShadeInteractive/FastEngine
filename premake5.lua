workspace "FastEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

IncludeDir["GLFW"] = "FastEngine/ThirdParties/GLFW/include"
IncludeDir["ImGui"] = "FastEngine/ThirdParties/imgui/include"

include "FastEngine/ThirdParties/imgui"
include "FastEngine/ThirdParties/GLFW"

project "FastEngine"
	location "FastEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "fepch.h"
	pchsource "FastEngine/Source/FastEngine/fepch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/ThirdParties/spdlog/include;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"ImGui"

	}

	filter "system:windows"
		cppdialect "C++11"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
			"FE_BUILD_DLL",
			"FE_ENABLE_ASSERT"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		symbols "On"

	filter "configurations:Debug"
		defines "FE_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "FE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"FastEngine/ThirdParties/spdlog/include;",
		"FastEngine/Source"
	}

	links
	{
		"FastEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		symbols "On"

	filter "configurations:Debug"
		defines "FE_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "FE_DIST"
		optimize "On"
