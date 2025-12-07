#pragma once

#ifdef CL_PLATFORM_WINDOWS
	#ifdef CL_BUILD_DLL
		#define COLONY_API __declspec(dllexport)
	#else
		#define COLONY_API __declspec(dllimport)
	#endif
#else
	#error
#endif
