#pragma once

#ifdef KN_PLATFORM_WINDOWS
	#ifdef KN_BUILD_DLL
		#define KANTO_API __declspec(dllexport)
	#else
		#define KANTO_API __declspec(dllimport)
	#endif
#else
	#error Kanto only supports windows
#endif

#ifdef KN_DEBUG
#define KN_ENABLE_ASSERTS
#endif

#ifdef KN_ENABLE_ASSERTS
// Currently accepts at least the condition and one additional parameter (the message) being optional
#define KN_ASSERT(x, ...) { if (!(x)) { KN_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();} }
#define KN_CORE_ASSERT(x, ...) { if(!(x)) { KN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();  } }
#else
#define KN_ASSERT(x, ...)
#define KN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)