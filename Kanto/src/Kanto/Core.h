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