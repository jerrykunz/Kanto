#pragma once
#include <Kanto/Core.h>
#include <Kanto/Events/Event.h>
#include "Window.h"

namespace Kanto
{
	class KANTO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		
	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined in client
	Application* CreateApplication();

}
