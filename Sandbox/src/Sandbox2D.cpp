#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	KN_PROFILE_FUNCTION();
	m_CheckerboardTexture = Kanto::Texture2D::Create("res/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	KN_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Kanto::Timestep ts)
{
	KN_PROFILE_FUNCTION();

	// Update
	{
		KN_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		KN_PROFILE_SCOPE("Renderer Prep");
		Kanto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Kanto::RenderCommand::Clear();
	}

	{
		KN_PROFILE_SCOPE("Renderer Draw");
		Kanto::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// Hazel::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Kanto::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Kanto::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Kanto::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Kanto::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	KN_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Kanto::Event& e)
{
	m_CameraController.OnEvent(e);
}