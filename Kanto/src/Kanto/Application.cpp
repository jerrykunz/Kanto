#include "knpch.h"
#include "Kanto/Application.h"
#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/Log.h"

#include "glad/glad.h"

namespace Kanto
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		KN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//if event e is of the type WindowCloseEvent, we execute this function and set it to handled
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

		KN_CORE_TRACE("{0}", e);

		//go through all the layers until it is set as handled. note that now it does one round even if the event is handled from the beginning
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{			
			(*--it)->OnEvent(e); 
			if (e.Handled)
				break;
		}

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent &x)
	{
		m_Running = false;
		return true;
	}
	

}


