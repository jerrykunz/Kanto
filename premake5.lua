workspace "Kanto"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- needs to be before includedir crap
	startproject "Sandbox"

	-- Include directories relative to root folder (solution directory)
	-- this is a struct where you can add other dependencies than glfw
	IncludeDir = {}
	IncludeDir["GLFW"] = "Kanto/vendor/GLFW/include"
	IncludeDir["Glad"] = "Kanto/vendor/Glad/include"
	IncludeDir["ImGui"] = "Kanto/vendor/ImGui"

	--this somehow links the glfw premake5.lua to this file, kind of like #include
	include "Kanto/vendor/GLFW"
	include "Kanto/vendor/Glad"
	include "Kanto/vendor/ImGui"

	project "Kanto"
		location "Kanto"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" ..outputdir .. "/%{prj.name}")
		objdir ("obj/" ..outputdir .. "/%{prj.name}")

		pchheader "knpch.h"
		pchsource "Kanto/src/knpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Kanto/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}"
		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"KN_PLATFORM_WINDOWS",
				"KN_BUILD_DLL",
				"GLFW_INCLUDE_NONE" -- so we don't include any OPENGL headers while we initialize glfw, so glad works better
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations:Debug"
			defines "KN_DEBUG"
			buildoptions "/MDd" -- issue remains
			--runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "KN_RELEASE"
			buildoptions "/MD"
			--runtime "Release"
			optimize "On"		

		filter "configurations:Dist"
			defines "KN_DIST"
			buildoptions "/MD"
			--runtime "Release"
			optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" ..outputdir .. "/%{prj.name}")
		objdir ("obj/" ..outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Kanto/vendor/spdlog/include",
			"Kanto/src"
		}

		links
		{
			"Kanto"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"KN_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "KN_DEBUG"
			buildoptions "/MDd"
			--runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "KN_RELEASE"
			buildoptions "/MD"
			--runtime "Release"
			optimize "On"		

		filter "configurations:Dist"
			defines "KN_DIST"
			buildoptions "/MD"
			--runtime "Release"
			optimize "On"