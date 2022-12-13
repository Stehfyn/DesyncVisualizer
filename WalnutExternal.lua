-- WalnutExternal.lua
--VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
--IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["OpenGL"] = "../vendor/GL"
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["assimp"] = "../vendor/assimp/include"
IncludeDir["glew"] = "../vendor/glew/include"
IncludeDir["stb"] = "../vendor/stb"

LibraryDir = {}
--LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
--LibraryDir["OpenGL"] = "../vendor/GL/Lib"
LibraryDir["assimp"] = "../vendor/assimp/bin" --gotta do per config yucky
LibraryDir["glew"] = "../vendor/glew/bin"

Library = {}
--Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
--Library["OpenGL"] = "%{LibraryDir.OpenGL}/glew32.lib"
Library["assimp"] = "%{LibraryDir.assimp}/" .. outputdir .. "/assimp/assimp.lib"
Library["glew"] = "%{LibraryDir.glew}/" .. outputdir .. "/glew/glew.lib"

group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
   include "vendor/assimp"
   include "vendor/glew"
   --include "vendor/SOIL2"
   --externalproject "assimp"
       --location "vendor/assimp/code"
	   --uuid "35F5D00A-3DBD-35A7-8EFF-93D0C8DC6A08"
	   --kind "StaticLib"
	   --language "C++"
   --include "vendor/Creek"
group ""

group "Core"
include "Walnut"
group ""