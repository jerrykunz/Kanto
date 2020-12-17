#include "Application.h"
#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/Log.h"

namespace Kanto
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}


	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		KN_TRACE(e);
		while (true);
	}

}


