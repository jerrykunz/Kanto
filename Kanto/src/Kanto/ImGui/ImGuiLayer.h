#pragma once

#include "Kanto/Layer.h"

#include "Kanto/Events/ApplicationEvent.h"
#include "Kanto/Events/KeyEvent.h"
#include "Kanto/Events/MouseEvent.h"

namespace Kanto {

	class KANTO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}