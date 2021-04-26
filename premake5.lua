workspace "CCN_Lab"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release"
	}

project "SpikeSim"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/")
	objdir ("bin-int/")

	pchheader "sspch.h"
	pchsource "src/sspch.cpp"

	files
	{
		"src/**.cpp",
    "src/**.h"
	}

	includedirs
	{
		"src/",
		"vendor/spdlog/include",
		"vendor/matplotlib-cpp",
		"/usr/include/python3.5"
	}

	links
	{
		"python3.5m"
	}
