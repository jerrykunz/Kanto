#pragma once
#include <Kanto/Core.h>
#include <Kanto/Events/Event.h>
#include "Kanto/Events/ApplicationEvent.h"
#include "Window.h"

namespace Kanto
{
	class KANTO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		
	private:
		bool OnWindowClosed(WindowCloseEvent& x);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined in client
	Application* CreateApplication();

}
