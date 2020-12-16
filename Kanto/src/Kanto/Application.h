#pragma once
#include "Core.h"

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
