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
	IncludeDir["glm"] = "Kanto/vendor/glm"

	--this somehow links the glfw premake5.lua to this file, kind of like #include
	--group = folder in visual studio
	group "Dependencies"	
		include "Kanto/vendor/GLFW"
		include "Kanto/vendor/Glad"
		include "Kanto/vendor/ImGui"
		--include "Kanto/vendor/glm/glm" -- not a project, header only so not included
	group ""



	project "Kanto"
		location "Kanto"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"	
		staticruntime "On"		--On for "Multithreaded" off for "MultithreadedDLL" or MT/MD choice. 'runtime "Debug"/"Release"' sets the d flag MTd/MDd
		

		targetdir ("bin/" ..outputdir .. "/%{prj.name}")
		objdir ("obj/" ..outputdir .. "/%{prj.name}")

		pchheader "knpch.h"
		pchsource "Kanto/src/knpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp", --not really needed as this is a header only lib, but let's stay consistent
			"%{prj.name}/vendor/glm/glm/**.inl" --inline and template stuff here
		}

		includedirs
		{
			"Kanto/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}"
		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		filter "system:windows"		
			systemversion "latest"

			defines
			{
				"KN_PLATFORM_WINDOWS",
				"KN_BUILD_DLL",
				"GLFW_INCLUDE_NONE" -- so we don't include any OPENGL headers while we initialize glfw, so glad works better
			}

			--no longer necessary as we ditched the dll for static runtime because of performance and warnings on compile
			--postbuildcommands
			--{
				--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
				--("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"") --fixes fail on first time build
			--}

		filter "configurations:Debug"
			defines "KN_DEBUG"
			--buildoptions "/MDd" -- OLD
			runtime "Debug" --sets the debug flag: MT/MTd or MD/MDd, depending on staticruntime
			symbols "On"

		filter "configurations:Release"
			defines "KN_RELEASE"
			--buildoptions "/MD" --OLD
			runtime "Release"
			optimize "On"		

		filter "configurations:Dist"
			defines "KN_DIST"
			--buildoptions "/MD" --OLD
			runtime "Release"
			optimize "On"



	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"	
		staticruntime "On"

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
			"Kanto/src",
			"Kanto/vendor",
			"%{IncludeDir.glm}"
		}

		links
		{
			"Kanto"
		}

		filter "system:windows"		
			systemversion "latest"

			defines
			{
				"KN_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "KN_DEBUG"
			--buildoptions "/MDd"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "KN_RELEASE"
			--buildoptions "/MD"
			runtime "Release"
			optimize "On"		

		filter "configurations:Dist"
			defines "KN_DIST"
			--buildoptions "/MD"
			runtime "Release"
			optimize "On"