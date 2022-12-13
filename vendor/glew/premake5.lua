--workspace "GLEW"
--    architecture "x64"
--    configurations { "Debug", "Release", "Dist" }
--    startproject "GLEW"
--
--    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GLEW"
	kind "StaticLib"
	language "C"
	--staticruntime "off"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"include"
	}

	files
	{
		"premake5.lua",
		"include/GL/*.h",
		"src/glew.c",
		"src/glewinfo.c",
	}

	defines
	{
		"GLEW_STATIC",
		"GLEW_NO_GLU",
		--"GLEW_BUILD"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
       	symbols "off"

	filter "system:linux"
		links
		{
			"GL",
		}

	filter "system:macosx"
		linkoptions
		{
			"-Wl,-install_name,@executable_path/libglew.dylib", -- set the install name to load us from the folder of the loader
			"-framework OpenGL",
			"-framework AGL",
			"-framework Cocoa",
		}

	filter "system:windows"
		links
		{
			"opengl32",
		}
