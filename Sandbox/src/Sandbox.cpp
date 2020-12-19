#include <Kanto.h>

//test
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


class ExampleLayer : public Kanto::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		auto cam = camera(1.0f, { 1.0f, 2.0f });
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