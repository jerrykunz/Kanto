workspace "Kanto"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	startproject "Sandbox"

	project "Kanto"
		location "Kanto"
		kind "SharedLib"
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
			"Kanto/src",
			"%{prj.name}/vendor/spdlog/include"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"KN_PLATFORM_WINDOWS",
				"KN_BUILD_DLL"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations.Debug"
			defines "KN_DEBUG"
			symbols "On"

		filter "configurations.Release"
			defines "KN_DEBUG"
			optimize "On"		

		filter "configurations.Release"
			defines "KN_DIST"
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

		filter "configurations.Debug"
			defines "KN_DEBUG"
			symbols "On"

		filter "configurations.Release"
			defines "KN_DEBUG"
			optimize "On"		

		filter "configurations.Release"
			defines "KN_DIST"
			optimize "On"