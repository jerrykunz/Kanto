#pragma once

#ifdef KN_PLATFORM_WINDOWS

extern Kanto::Application* Kanto::CreateApplication();


int main(int argc, char** argv)
{
	Kanto::Log::Init();

	KN_CORE_WARN("Initialized log!");
	int a = 5;
	KN_CLIENT_INFO("number is {0}", a);

	auto app = Kanto::CreateApplication();
	app->Run();
	delete app;
}




#endif