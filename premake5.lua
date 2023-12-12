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
IncludeDir["ImGui"] = "FastEngine/ThirdParties/imgui"
IncludeDir["Glad"] = "FastEngine/ThirdParties/Glad/include"
IncludeDir["glm"] = "FastEngine/ThirdParties/glm"

include "FastEngine/ThirdParties/imgui"
include "FastEngine/ThirdParties/GLFW"
include "FastEngine/ThirdParties/Glad"

project "FastEngine"
	location "FastEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	toolset "v143"
	staticruntime "on"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "fepch.h"
	pchsource "FastEngine/Source/FastEngine/fepch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/ThirdParties/glm/glm/**.hpp",
		"%{prj.name}/ThirdParties/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/ThirdParties/spdlog/include;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"

	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
			"FE_BUILD_DLL",
			"FE_ENABLE_ASSERT",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "FE_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "FE_DIST"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

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
		"FastEngine/Source",
		"%{IncludeDir.glm}"
	}

	links
	{
		"FastEngine"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		toolset "v143"

		defines
		{
			"FE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FE_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "FE_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "FE_DIST"
		buildoptions "/MD"
		optimize "on"
