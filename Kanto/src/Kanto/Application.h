#pragma once
#include "Core.h"
#include "Kanto/Events/Event.h"

namespace Kanto
{
	class KANTO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//to be defined in client
	Application* CreateApplication();

}
