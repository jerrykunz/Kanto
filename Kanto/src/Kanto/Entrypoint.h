#pragma once

#ifdef KN_PLATFORM_WINDOWS

extern Kanto::Application* Kanto::CreateApplication();


int main(int argc, char** argv)
{
	printf("Kanto engine");
	auto app = Kanto::CreateApplication();
	app->Run();
	delete app;
}




#endif