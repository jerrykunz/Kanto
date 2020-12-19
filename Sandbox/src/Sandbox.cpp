#include <Kanto.h>

class ExampleLayer : public Kanto::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		if (Kanto::Input::IsKeyPressed(KN_KEY_TAB))
			KN_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Kanto::Event& event) override
	{
		if (event.GetEventType() == Kanto::EventType::KeyPressed)
		{
			Kanto::KeyPressedEvent& e = (Kanto::KeyPressedEvent&)event;
			if (e.GetKeyCode() == KN_KEY_TAB)
				KN_TRACE("Tab key is pressed (event)!");
			KN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};


class Sandbox : public Kanto::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Kanto::ImGuiLayer());
	}	

	~Sandbox()
	{

	}
};

Kanto::Application* Kanto::CreateApplication()
{
	return new Sandbox();
}