#include <Kanto.h>

class Sandbox : public Kanto::Application
{
public:
	Sandbox()
	{

	}	

	~Sandbox()
	{

	}
};

Kanto::Application* Kanto::CreateApplication()
{
	return new Sandbox();
}