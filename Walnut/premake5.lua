project "Walnut"
   kind "StaticLib"
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
      "src",

      "../vendor/imgui",
      "../vendor/glfw/include",
      --"%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
	   "%{IncludeDir.assimp}",
	   "%{IncludeDir.stb}",
      "%{IncludeDir.glew}"
   }

   links
   {
       "ImGui",
       "GLFW",
	   "assimp",
      "GLEW",
       --"%{Library.Vulkan}",
   }

   defines
   {
      "GLEW_STATIC"
   }

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"
