#pragma once
#include <Kanto/Core.h>
#include "Kanto/LayerStack.h"
#include <Kanto/Events/Event.h>
#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Kanto/Renderer/Shader.h"
#include "Kanto/Renderer/Buffer.h"
#include "Kanto/Renderer/VertexArray.h"

namespace Kanto
{
	class KANTO_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack; 

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();

}
