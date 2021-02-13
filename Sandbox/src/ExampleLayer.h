#pragma once

#include "Kanto.h"

class ExampleLayer : public Kanto::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Kanto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Kanto::Event& e) override;
private:
	Kanto::ShaderLibrary m_ShaderLibrary;
	Kanto::Ref<Kanto::Shader> m_Shader;
	Kanto::Ref<Kanto::VertexArray> m_VertexArray;

	Kanto::Ref<Kanto::Shader> m_FlatColorShader;
	Kanto::Ref<Kanto::VertexArray> m_SquareVA;

	Kanto::Ref<Kanto::Texture2D> m_Texture, m_ChernoLogoTexture;

	Kanto::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

