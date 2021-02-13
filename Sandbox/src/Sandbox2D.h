#pragma once

#include "Kanto.h"

class Sandbox2D : public Kanto::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Kanto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Kanto::Event& e) override;
private:
	Kanto::OrthographicCameraController m_CameraController;

	// Temp
	Kanto::Ref<Kanto::VertexArray> m_SquareVA;
	Kanto::Ref<Kanto::Shader> m_FlatColorShader;

	Kanto::Ref<Kanto::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};