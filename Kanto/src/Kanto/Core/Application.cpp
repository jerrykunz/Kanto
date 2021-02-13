#include "knpch.h"
#include "Kanto/Core/Application.h"
#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/Core/Input.h"
#include "Kanto/Core/Log.h"

#include "Kanto/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Kanto
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		KN_PROFILE_FUNCTION();

		KN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(KN_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		KN_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		KN_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		//layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		KN_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		//layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		KN_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		//if event e is of the type WindowCloseEvent, we execute this function and set it to handled
		dispatcher.Dispatch<WindowCloseEvent>(KN_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(KN_BIND_EVENT_FN(Application::OnWindowResize));

		KN_CORE_TRACE("{0}", e);

		//go through all the layers from front to back until it is set as handled. note that now it does one round even if the event is handled from the beginning
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{			
			(*--it)->OnEvent(e); 
			if (e.Handled)
				break;
		}

	}

	void Application::Run()
	{
		KN_PROFILE_FUNCTION();
		while (m_Running)
		{
			KN_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					KN_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
				
				m_ImGuiLayer->Begin();
				{
					KN_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();

			}


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent &x)
	{
		m_Running = false;
		return true;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		KN_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}


