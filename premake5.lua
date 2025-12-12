workspace "Colony"    -- 解决方案名称
	architecture "x64"    -- x64架构

	configurations    -- 配置模式一共有三种
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"    -- 输出目录

-- 相对根目录的附加包含目录路径
IncludeDir = {}
IncludeDir["GLFW"] = "Colony/vendor/GLFW/include"
IncludeDir["Glad"] = "Colony/vendor/Glad/include"

include "Colony/vendor/GLFW"
include "Colony/vendor/Glad"

project "Colony"    -- 生成Colony项目
	location "Colony"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")    -- build文件.dll/.lib/.exe的输出目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")    -- build中间文件.o的输目录

	pchheader "clpcl.h"
	pchsource "Colony/src/clpcl.cpp"

	files
	{
		"%{prj.name}/src/**.h",     -- 添加文件到工作区
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",    -- 附加包含目录
		"Colony/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"    -- C++标准
		staticruntime "On"    -- 静态运行库
		systemversion "latest"    -- 最新版本的SDK

		defines
		{
			"CL_PLATFORM_WINDOWS",    -- windows平台 -- 这是代码内ifdef需要
			"CL_BUILD_DLL",    -- 是否生成为dll -- 代码内ifdef需要
			"GLFW_INCLUDE_NONE"    -- GLFW在include时排除所有系统级别的OpenGL头文件
		}

		postbuildcommands -- 生成后处理命令 -- 复制文件
		{
			('if not exist "%{wks.location}/bin/' .. outputdir .. '/Sandbox" mkdir "%{wks.location}/bin/' .. outputdir .. '/Sandbox"'),
			('{COPY} "%{wks.location}/bin/' .. outputdir .. '/Colony/Colony.dll" "%{wks.location}/bin/' .. outputdir .. '/Sandbox/"')
		}

		buildoptions "/utf-8" -- 命令行编译时使用/utf-8编码 -- spdlog库要求

	filter "configurations:Debug"
		defines "CL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CL_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Colony/vendor/spdlog/include",
		"Colony/src"
	}

	links
	{
		"Colony"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CL_PLATFORM_WINDOWS",
		}

		buildoptions "/utf-8"

	filter "configurations:Debug"
		defines "CL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CL_DIST"
		buildoptions "/MD"
		optimize "On"
