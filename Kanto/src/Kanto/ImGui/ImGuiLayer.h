#pragma once

#include "Kanto/Core/Layer.h"

#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/Events/KeyEvent.h"
#include "Kanto/Events/MouseEvent.h"

namespace Kanto {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}