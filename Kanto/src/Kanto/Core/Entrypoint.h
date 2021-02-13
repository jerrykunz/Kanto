#pragma once
#include "Kanto/Core/Core.h"

#ifdef KN_PLATFORM_WINDOWS

extern Kanto::Application* Kanto::CreateApplication();


int main(int argc, char** argv)
{
	Kanto::Log::Init();
	KN_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Kanto::CreateApplication();
	KN_PROFILE_END_SESSION();

	KN_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	KN_PROFILE_END_SESSION();

	KN_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	KN_PROFILE_END_SESSION();
}




#endif