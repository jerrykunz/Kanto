#include <Kanto.h>

class ExampleLayer : public Kanto::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		KN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Kanto::Event& event) override
	{
		KN_TRACE("{0}", event);
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