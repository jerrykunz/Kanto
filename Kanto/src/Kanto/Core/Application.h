#pragma once
#include <Kanto/Core/Core.h>
#include "Kanto/Core/LayerStack.h"
#include <Kanto/Events/Event.h>
#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/ImGui/ImGuiLayer.h"
#include "Kanto/Core/Window.h"


namespace Kanto
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClosed(WindowCloseEvent& x);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack; 

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();

}
