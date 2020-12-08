workspace "AoC 2020"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

local outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "AoC 2020"
	location "AoC 2020"
	kind "ConsoleApp"
	language "C++"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-intermediate/" .. outputdir .. "/%{prj.name}")
	debugdir("bin/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
   	pchsource("%{prj.name}/src/pch.cpp")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.txt",
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	libdirs
	{
	}

	links 
	{
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	    	buildoptions 
		{
		}

		postbuildcommands
		{
		    "{COPY} \"src/days/day01/day01_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",
		    "{COPY} \"src/days/day02/day02_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",
		    "{COPY} \"src/days/day03/day03_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",
		    "{COPY} \"src/days/day04/day04_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",
    		    "{COPY} \"src/days/day05/day05_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",
    		    "{COPY} \"src/days/day06/day06_input.txt\" ../bin/" .. outputdir .. "\"/%{prj.name}\"",		    
		}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

