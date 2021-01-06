#include <Kanto.h>
#include  "ImGui/imgui.h"


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
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Kanto::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Kanto::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Kanto::VertexBuffer::Create(vertices, sizeof(vertices)));
		Kanto::BufferLayout layout = {
			{ Kanto::ShaderDataType::Float3, "a_Position" },
			{ Kanto::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Kanto::IndexBuffer> indexBuffer;
		indexBuffer.reset(Kanto::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		//SQUARE

		m_SquareVA.reset(Kanto::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Kanto::VertexBuffer> squareVB;
		squareVB.reset(Kanto::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Kanto::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Kanto::IndexBuffer> squareIB;
		squareIB.reset(Kanto::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);



		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";



		m_Shader.reset(new Kanto::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Kanto::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnUpdate(Kanto::Timestep ts) override
	{
		if (Kanto::Input::IsKeyPressed(KN_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Kanto::Input::IsKeyPressed(KN_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Kanto::Input::IsKeyPressed(KN_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Kanto::Input::IsKeyPressed(KN_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Kanto::Input::IsKeyPressed(KN_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Kanto::Input::IsKeyPressed(KN_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Kanto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Kanto::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Kanto::Renderer::BeginScene(m_Camera);

		Kanto::Renderer::Submit(m_BlueShader, m_SquareVA);
		Kanto::Renderer::Submit(m_Shader, m_VertexArray);

		Kanto::Renderer::EndScene();
	}

	void OnEvent(Kanto::Event& event) override
	{
		/*if (event.GetEventType() == Kanto::EventType::KeyPressed)
		{
			Kanto::KeyPressedEvent& e = (Kanto::KeyPressedEvent&)event;
			if (e.GetKeyCode() == KN_KEY_TAB)
				KN_TRACE("Tab key is pressed (event)!");
			KN_TRACE("{0}", (char)e.GetKeyCode());
		}*/
	}

	private:
		std::shared_ptr<Kanto::Shader> m_Shader;
		std::shared_ptr<Kanto::VertexArray> m_VertexArray;

		std::shared_ptr<Kanto::Shader> m_BlueShader;
		std::shared_ptr<Kanto::VertexArray> m_SquareVA;

		Kanto::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 5.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
};


class Sandbox : public Kanto::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Kanto::ImGuiLayer());
	}	

	~Sandbox()
	{

	}
};

Kanto::Application* Kanto::CreateApplication()
{
	return new Sandbox();
}