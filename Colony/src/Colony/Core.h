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

#ifdef CL_ENABLE_ASSERTS
#define CL_ASSERT(x, ...) { if(!(x)) { CL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CL_CORE_ASSERT(x, ...) { if(!(x)) { CL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define CL_ASSERT(x, ...)
#define CL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
