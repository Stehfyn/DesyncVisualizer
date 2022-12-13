-- premake5.lua
include "vendor/bin/premake_customization/solution_items.lua"

workspace "WalnutApp"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "WalnutApp"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    solution_items {"premake5.lua", "WalnutExternal.lua"}
    
include "WalnutExternal.lua"
include "WalnutApp"