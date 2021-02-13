#include "knpch.h"
#include "Kanto/Core/Input.h"

#ifdef KN_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Kanto {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef KN_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		KN_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}