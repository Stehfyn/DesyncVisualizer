project "WalnutApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "on"

    files 
    {
        "premake5.lua",
        "src/**.h", 
        "src/**.cpp" 
    }

    includedirs
    {
        "../vendor/imgui",
        "../vendor/glfw/include",

        "../Walnut/src",

      --"%{IncludeDir.VulkanSDK}",
	     "%{IncludeDir.OpenGL}",
        "%{IncludeDir.glm}",
	     "%{IncludeDir.assimp}",
        "%{IncludeDir.glew}",
    }

    links
    {
        "Walnut",
		  "opengl32.lib",
		--"glew32.lib",
		  "%{Library.assimp}",
        "%{Library.glew}"
    }

	 libdirs
	 {
	    --"../vendor/GL/Lib",
		"%{LibraryDir.assimp}",
      "%{LibraryDir.glew}"
	 }
    defines
    {
       "GLEW_STATIC"
    }
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "WL_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines { "WL_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        kind "WindowedApp"
        defines { "WL_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines { "WL_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
