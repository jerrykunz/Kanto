#include <Kanto.h>
#include <Kanto/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"




class Sandbox : public Kanto::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}	

	~Sandbox()
	{

	}
};

Kanto::Application* Kanto::CreateApplication()
{
	return new Sandbox();
}